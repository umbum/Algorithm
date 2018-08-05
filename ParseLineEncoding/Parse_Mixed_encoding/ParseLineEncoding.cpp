#include "stdafx.h"
#include "cppcore.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <stdlib.h>

#include <windows.h>
#pragma warning(disable : 4996)

using namespace std;
using namespace core;

enum {
	BUF_SIZE = 4096,    //128 K
	MAX_LINE_LEN = 4096
};
enum ENCODING {
	UTF32 = 32,
	UTF16 = 16,
	UTF8 = 8,
	EUCKR = 949,
	ERR = -1
};
class AutoDecoder {
private:
	FILE * ifp;
	FILE* ofp;
	char buf[BUF_SIZE];
	wchar_t wobuf[BUF_SIZE];
public:
	AutoDecoder(const char* in_path, const char* out_path) {
		ifp = fopen(in_path, "rb");
		if (!ifp) {
			std::cout << "[*] failed to open input data" << std::endl;
			exit(EXIT_FAILURE);
		}
		else {
			std::cout << "[*] path : " << in_path << std::endl;
		}
		//ifs.rdbuf()->pubsetbuf(buf, BUF_SIZE);

		ofp = fopen(out_path, "wb");
		if (!ofp) {
			std::cout << "[*] failed to open output file" << std::endl;
			exit(EXIT_FAILURE);
		}
		//wofs.rdbuf()->pubsetbuf(wobuf, BUF_SIZE);
	}
	void tmp() {
		uint8_t byte;
		while ((byte = fgetc(ifp)) != EOF) {
			printf("%02hhx ", byte);
		}
	}
	~AutoDecoder() {
		fclose(ifp);
		fclose(ofp);
	}
	void decode() {
		// input data는 라인 단위로 인코딩이 변경됨.
		int read_count;
		uint8_t line[MAX_LINE_LEN];
		WORD dstbuf[4*1024];
		size_t encoded_num;
		while (!feof(ifp)) {
			if ((read_count = getLine(line, MAX_LINE_LEN)) == -1) {
				printf("[ERR] getLine exceed line_buf size");
				printHex((uint8_t*)line, MAX_LINE_LEN);
				exit(EXIT_FAILURE);
			}
			ENCODING code = checkLineEncoding(line, read_count);
			switch (code) {
			case ENCODING::UTF32:
				encoded_num = UTF32_TO_UTF16((DWORD*)line, read_count/2, (WORD*)dstbuf, read_count / 2);
				fseek(ifp, 3, SEEK_CUR);  // 0a 뒤의 00 00 00 건너뛰기.
				break;
			case ENCODING::UTF16:
				encoded_num = UTF16_TO_UTF16((WORD*)line, read_count, (WORD*)dstbuf, read_count);
				fseek(ifp, 1, SEEK_CUR);  // 0a 뒤의 00 건너뛰기.
				break;
			case ENCODING::EUCKR:
				encoded_num = EUCKR_TO_UTF16((char*)line, read_count, (WORD*)dstbuf, BUF_SIZE);
				encoded_num *= 2;
				break;
			case ENCODING::UTF8:
				encoded_num = UTF8_TO_UTF16((char*)line, read_count, (WORD*)dstbuf, BUF_SIZE);
				encoded_num *= 2;
				break;
			default:
				cout << "ERROR!!!! NOT MACHED" << endl;
				printHex((uint8_t*)line, read_count);
				exit(EXIT_FAILURE);
			}
			fwrite(dstbuf, 1, encoded_num, ofp);
			fwrite("\n", 1, encoded_num, ofp);
			//::Sleep(300);
		}
	}

	///////////////////////// CHECK ENCODING ////////////////////////////
	ENCODING checkLineEncoding(const uint8_t* line, int len) {
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
			if (check_cp949(line, len))      return ENCODING::EUCKR;
			else if (check_utf8(line, len))  return ENCODING::UTF8;
			else                             return ENCODING::ERR;
		}
	}

	bool check_utf32(const uint8_t *line, int len) {
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
		return true;
	}
	bool check_utf16(const uint8_t* line, int len) {
		// check 1.
		if (len % 2 != 0) {
			return false;
		}
		// check 2. 4byte. [D800~DBFF][DC00~DFFF]
		//isInCRange(line[i], 0xd8, 0xdb) && isInCRange(line[i + 2], 0xdc, 0xdf);
		return true;
	}
	bool check_utf8(const uint8_t* line, int len) {
		if (len == 1) {
			if (line[0] == 0x00)					 return false;
		}
		else if (len == 2) {
			if (line[0] == 0x00)					 return false;
			else if (isInCRange(line[2], 0xc2, 0xdf) &&
				!isInCRange(line[1], 0x80, 0xbf))    return false;
		}
		else {
			for (int i = 0; i < len - 2; i++) {
				if (line[i] == 0x00)				    	   return false;
				// utf8 2byte [c2~][80~bf]
				else if (isInCRange(line[i], 0xc2, 0xdf) &&
					!isInCRange(line[i + 1], 0x80, 0xbf))      return false;
				// utf8 3byte [e0~][80~bf][80~bf]
				else if (line[i] >= 0xe0 &&
					(!isInCRange(line[i + 1], 0x80, 0xbf) ||
						!isInCRange(line[i + 2], 0x80, 0xbf))) return false;
			}
		}
		return true;
	}
	bool check_cp949(const uint8_t* line, int len) {
		if (len == 1 && !isInCRange(line[0], 0x00, 0x7f)) return false;
		for (int i = 0; i < len - 1; i++) {
			if (isInCRange(line[i], 0, 0x7f)) {
				continue;
			}
			else if (isInCRange(line[i], 0xa1, 0xfe) && isInCRange(line[i + 1], 0xa, 0xfe)) {
				continue;
			}   //// below CP949 extension
			else if ((isInCRange(line[i], 0x81, 0xa0) || isInCRange(line[i], 0xa1, 0xc5)) &&
				(isInCRange(line[i + 1], 0x41, 0x5a) || isInCRange(line[i + 1], 0x61, 0x7a) || isInCRange(line[i + 1], 0x81, 0xfe))) {
				continue;
			}
			else if ((line[i] == 0xc6) && (isInCRange(line[i + 1], 0x41, 0x52))) {
				continue;
			}
			else {
				return false;
			}
		}
		return true;
	}
	inline bool isInCRange(int var, int a, int b) {
		// is variable in closed range?
		return (a <= var && var <= b) ? true : false;
	}

	///////////////////// PRINT & GET FILE DATA ////////////////////
	int getLine(uint8_t *line, int size) {
		// func does not guarantee that pos point next line. so you have to manually forward pos.
		// ifp have to be opened in binary mode.
		// e.g., 0a 00 00 00이면 00 00 00만큼 앞으로 감기 해야 다음 라인이 나온다.
		int count = 0;
		uint8_t byte;
		while ((byte = fgetc(ifp)) != EOF) {
			if (byte == EOF) {
				break;
			}
			if (byte == 0x0a)
				break;
			else if (size <= count) {
				return -1;    // err
			}
			*line++ = byte;
			count++;
		}
		return count;
	}
	void printHex(const uint8_t *bin, int size) {
		printf("::: ");
		size = (size < BUF_SIZE) ? size : BUF_SIZE;
		for (int i = 0; i < size; i++) {
			printf("%02hhx ", bin[i]);
		}
		printf("\n");
	}
};



int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "[*] input path has to be specified in argv[1]" << std::endl;
		return -1;
	}
	const char *out_path = (argc > 2) ? argv[2] : "decoded.txt";
	AutoDecoder d(argv[1], out_path);
	d.decode();
	printf("DONE!!!\n");
	return 0;
}

