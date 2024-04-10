import ctypes

class DynamicArray:
    def __init__(self):
        self.capacity = 1
        self.size = 0
        self.arr = self._create_array(self.capacity)

    def __getitem__(self, index):
        if not 0 <= index < self.size:
            raise IndexError('Index out of range')
        return self.arr[index]

    def __len__(self):
        return self.size

    def _create_array(self, capacity):
        return (ctypes.c_int * capacity)()

    def _resize(self, new_capacity):
        new_arr = self._create_array(new_capacity)
        for i in range(self.size):
            new_arr[i] = self.arr[i]
        self.arr = new_arr
        self.capacity = new_capacity

    def append(self, value):
        if self.size == self.capacity:
            self._resize(2 * self.capacity)
        self.arr[self.size] = value
        self.size += 1
    
    def push(self, value):
        self.append(value)

    def pop(self):
        if self.size == 0:
            raise IndexError('Empty array')
        value = self.arr[self.size - 1]
        self.size -= 1
        return value

    def display(self):
        for i in range(self.size):
            print(self.arr[i], end=' ')
        print()

if __name__ == "__main__":
    dynamic_array = DynamicArray()
    for i in range(15):
        dynamic_array.append(i)

    print("Dynamic Array:")
    dynamic_array.display()

    print("Size:", len(dynamic_array))
    print()
    print("Popping the last element:", dynamic_array.pop())
    print("Dynamic Array after popping:")
    dynamic_array.display()
    print("Size:", len(dynamic_array))
    print()
    print("Pushing an element: 99")
    dynamic_array.push(99)
    print("Dynamic Array after pushing 99:")
    
    dynamic_array.display()