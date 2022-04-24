from random import sample
from string import printable as char_set
from pyperclip import copy

length = int(input("password length: "))
print(passwd := ''.join(sample(char_set.strip(), length)))
copy(passwd)
