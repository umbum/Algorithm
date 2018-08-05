#include "stdafx.h"
#include "cppcore.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <stdlib.h>

#include <windows.h>

using namespace std;
using namespace core;

enum {
	BUF_SIZE = 4096,    //128 K
	MAX_LINE_LEN = 1024
};

enum ENCODING {
	UTF32 = 32,
	UTF16 = 16,
	UTF8 = 8,
	EUCKR = 949,
	ERR = -1
};
class AutoDecoder2 {
private:
	ifstream ifs;
	wofstream wofs;
	FILE* ifp;
	FILE* ofp;
	char buf[BUF_SIZE];
	wchar_t wobuf[BUF_SIZE];
public:
	AutoDecoder(char* fpath) {
		ifs.open(fpath, std::ios::binary);
		if (ifs.fail()) {
			std::cout << "[*] failed to open input data" << std::endl;
			exit(EXIT_FAILURE);
		}
		else {
			std::cout << "[*] path : " << fpath << std::endl;
		}
		ifs.rdbuf()->pubsetbuf(buf, BUF_SIZE);

		wofs.open("C:\\Users\\umbum\\source\\repos\\Parse_Mixed_encoding\\decoded.txt");
		if (wofs.fail()) {
			std::cout << "[*] failed to open output file" << std::endl;
			exit(EXIT_FAILURE);
		}
		wofs.rdbuf()->pubsetbuf(wobuf, BUF_SIZE);
	}
	~AutoDecoder() {
		ifs.close();
		delete buf;
	}
	void decode() {
		// input data는 라인 단위로 인코딩이 변경됨.
		int read_count;
		uint8_t line[MAX_LINE_LEN];
		WORD dstbuf[1024];
		size_t encoded_num;
		while (!ifs.eof()) {
			read_count = getLine(line);
			//printHex(line, read_count);
			ENCODING code = checkLineEncoding(line, read_count);
			switch (code) {
			case ENCODING::UTF32:
				printHex((uint8_t*)line, read_count);
				encoded_num = UTF32_TO_UTF16((DWORD*)line, read_count / 2, (WORD*)dstbuf, read_count / 2);
				printHex((uint8_t*)dstbuf, encoded_num);
				//wofs.write((wchar_t*)dstbuf, encoded_num);
				wofs << dstbuf;
				ifs.rdbuf()->pubseekoff(3, ifs.cur);  // 0a 뒤의 00 00 00 건너뛰기.
				break;
			case ENCODING::UTF16:
				encoded_num = UTF16_TO_UTF16((WORD*)line, read_count, (WORD*)dstbuf, read_count);
				wofs << dstbuf;
				ifs.rdbuf()->pubseekoff(1, ifs.cur);  // 0a 뒤의 00 00 00 건너뛰기.
				break;
			case ENCODING::EUCKR:
				//printHex((uint8_t*)line, read_count);
				encoded_num = EUCKR_TO_UTF16((char*)line, read_count, (WORD*)dstbuf, BUF_SIZE);
				encoded_num *= 2;
				//printHex((uint8_t*)dstbuf, encoded_num);
				wofs << wobuf;
				break;
			case ENCODING::UTF8:
				//printHex((uint8_t*)line, read_count);
				encoded_num = UTF8_TO_UTF16((char*)line, read_count, (WORD*)dstbuf, BUF_SIZE);
				encoded_num *= 2;
				//printHex((uint8_t*)dstbuf, encoded_num);
				wofs << wobuf;
				break;
			default:
				cout << "ERROR!!!! NOT MACHED" << endl;
				exit(EXIT_FAILURE);
			}
			//::Sleep(300);
		}
		wofs.flush();
	}

	ENCODING checkLineEncoding(uint8_t* line, int len) {
		bool is_zero_detected = false;
		for (int i = 0; i < len; i++) {
			if (line[i] == 0x00) {
				is_zero_detected = true;
				break;
			}
		}
		if (is_zero_detected) {
			if (check_utf32(line, len))      return ENCODING::UTF32;
			else if (check_utf16(line, len)) return ENCODING::UTF16;
			else                             return ENCODING::ERR;
		}
		else {
			if (check_euckr(line, len))     return ENCODING::EUCKR;
			else if (check_utf8(line, len)) return ENCODING::UTF8;
			else                            return ENCODING::ERR;
		}
	}

	bool check_utf32(uint8_t *line, int len) {
		// check 1.
		if (len % 4 != 0) {
			return false;
		}
		// check 2.
		int i = 3;
		while (i < len) {
			if (line[i] != 0 || line[i - 1] != 0) {
				return false;
			}
			i += 4;
		}
		//cout << "UTF32  : [TRUE]" << endl;
		return true;
	}
	bool check_utf16(uint8_t* line, int len) {
		// check 1.
		if (len % 2 != 0) {
			return false;
		}
		//cout << "UTF16  : [TRUE]" << endl;
		return true;
	}
	bool check_utf8(uint8_t* line, int len) {
		if (len == 1) {
			if (line[0] == 0x00)					 return false;
		}
		else if (len == 2) {
			if (line[0] == 0x00)					 return false;
			else if (isInCRange(line[2], 0xc2, 0xdf) &&
				!isInCRange(line[1], 0x80, 0xbf)) return false;
		}
		else {
			for (int i = 0; i < len - 2; i++) {
				if (line[i] == 0x00)					 return false;
				// utf8의 2byte는 0xc2~ 0x80~0xbf 로 구성.
				else if (isInCRange(line[i], 0xc2, 0xdf) &&
					!isInCRange(line[i + 1], 0x80, 0xbf)) return false;
				// utf8의 3byte는 0xe0~ 0x80~0xbf 0x80~0xbf 로 구성.
				else if (line[i] >= 0xe0 &&
					(!isInCRange(line[i + 1], 0x80, 0xbf) ||
						!isInCRange(line[i + 2], 0x80, 0xbf))) return false;
			}
		}
		//cout << "UTF8   : [TRUE]" << endl;
		return true;
	}
	bool check_euckr(uint8_t* line, int len) {
		for (int i = 0; i < len; i++) {
			if (!(isInCRange(line[i], 0, 0x7f) || (isInCRange(line[i], 0xa1, 0xfe)))) {
				return false;
			}
		}
		//cout << "EUCKR  : [TRUE]" << endl;
		return true;
	}
	inline bool isInCRange(int var, int a, int b) {
		// is variable in closed range?
		if (a <= var && var <= b)   return true;
		return false;
	}
	int getLine(uint8_t *line) {
		// func does not guarantee that pos point next line. so you have to manually forward pos.
		// e.g., 0a 00 00 00이면 00 00 00만큼 앞으로 감기 해야 다음 라인이 나온다.
		int count = 0;
		uint8_t byte;
		while (ifs.rdbuf()->sgetn((char*)&byte, 1)) {
			if (byte == 0x0a)
				break;
			*line++ = byte;
			count++;
		}
		return count;
	}
	void printHex(uint8_t *bin, int size) {
		printf("::: ");
		size = (size < BUF_SIZE) ? size : BUF_SIZE;
		for (int i = 0; i < size; i++) {
			printf("%02hhx ", bin[i]);
		}
		cout << endl;
	}
};



int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "[*] input path has to be specified in argv[1]" << std::endl;
		return -1;
	}
	AutoDecoder d(argv[1]);
	d.decode();
	printf("DONE!!!\n");
	return 0;
}

