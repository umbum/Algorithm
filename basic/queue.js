class Queue {
    constructor(size) {
        this.data = [];
        this.front = 0;
        this.rear = 0;
        this.size = size;
        /**
         * full, empty를 구분하기 위해서, 내부적으로는 size + 1만큼의 공간이 필요하다.
         * rear + 1 == front 이면 full, rear == front 이면 empty.
         * 아니면 length 같은걸 하나 둬서 full, empty를 구분하는 것도 괜찮은 방법이다. 
         */
        this._size = size + 1;
        
    }

    enqueue(elem) {
        if (this.isFull) {
            throw "Queue is full";
        }

        this.data[this.rear] = elem;
        this.rear = (this.rear + 1) % this._size;
    }

    dequeue() {
        if (this.isEmpty) {
            throw "Queue is empty";
        }
        
        const elem = this.data[this.front];
        this.front = (this.front + 1) % this._size;
        return elem;
    }

    get isEmpty() {
        return (this.front === this.rear) ? true : false;
    }

    get isFull() {
        return ((this.rear + 1) % this._size === this.front) ? true : false;
    }
    
    get(i) {
        return this.data[i];
    }
}