import random
import numpy as np

# Hash Table
class HashTable:
    def __init__(self, table_size):
        self.size = table_size
        self.hash_table = [0 for a in range(self.size)]
        
    def getKey(self, data):
        self.key = int(data)
        print(self.key)
        return self.key
    
    def hashFunction(self, key):
        return key % self.size

    def getAddress(self, key):
        myKey = self.getKey(key)
        hash_address = self.hashFunction(myKey)
        return hash_address
    
    def save(self, key, value):
        hash_address = self.getAddress(key)
        self.hash_table[hash_address] = value
        
    def read(self, key):
        hash_address = self.getAddress(key)
        return self.hash_table[hash_address]
    
    def delete(self, key):
        hash_address = self.getAddress(key)
        
        if self.hash_table[hash_address] != 0:
            self.hash_table[hash_address] = 0
            return True
        else:
            return False

example = "75공 3014"
print(example[:2]+example[-4:])

examples = ['75공3014', '82공3015', '50공2208', '34공2157', '63공1000', '22공7002', '75공9044', '33공9996', '43공2777', '53공1051']
# Test Code
h_table = HashTable(36)
for example in examples
    h_table.save(example[:2]+example[-4:], example)

# for i in range(36):
#     seed = np.random.seed = i
#     car_num = np.random.randint(1000, 9999)
#     h_table.save(str(i), str(car_num))

#h_table.delete('d')

print(h_table.hash_table)