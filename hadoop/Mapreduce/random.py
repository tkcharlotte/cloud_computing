#coding:utf-8
import random
import string
for i in range(1,6):
    file_name = "File%s.txt"%(str(i))
    f = open(file_name, "a+")
    for j in range(1,40):
        name = random.sample(string.ascii_letters + string.digits, 3)
        score = random.randint(1, 100)
        f.writelines(str(j)+" ")
        f.writelines("".join(name)+" ")
        f.writelines(str(score))
        f.writelines("\n")
    f.close()
print "finish"
