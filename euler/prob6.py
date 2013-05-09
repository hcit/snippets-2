from math import pow 

def prob5(num):
	return pow(sum([x for x in range(num+1)]),2) - sum([x*x for x in range(num+1)])

if __name__ == "__main__":
	print prob5(100)


