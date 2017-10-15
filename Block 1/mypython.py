#!/usr/bin/python3

import random
import string
file = open('./file1.txt','w')
string1 = ""
for x in range(0, 10):
	string1 += random.choice(string.ascii_letters)

file.write(string1)
file.close()

file = open('./file2.txt','w')
string2 = ""
for x in range(0, 10):
	string2 += random.choice(string.ascii_letters)

file.write(string2)
file.close()

file = open('./file3.txt','w')
string3 = ""
for x in range(0, 10):
	string3 += random.choice(string.ascii_letters)

file.write(string3)
file.close()

print 'file1.txt contains: %s' % string1
print 'file2.txt contains: %s' % string2
print 'file3.txt contains: %s' % string3

from random import randint
x = randint(1,42)
y = randint(1,42)
z = x * y

print "%u * %u = %u" % (x, y, z)
