import sys,time
def prob5(start,end):
	start_t = time.time()
	tmp = 2 * end
	while 1:
		for i in range(start,end+1):
			if (tmp %i ) != 0:
				break
			elif i == end:
				print "Ans --> %d Elapsed Time --> %f" %(tmp,time.time() - start_t)
				sys.exit(0)
		tmp = tmp + end

prob5(1,20)

