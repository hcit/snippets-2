import sys
count = 0

for a in range(0,10):
    table = [False,False,False,False,False,False,False,False,False,False]
    table[a] = True
    for b in range(0,10):
        if not table[b]:
            table[b] = True
            for c in range(0,10):
                if not table[c]:
                    table[c] = True
                    for d in range(0,10):
                        if not table[d]:
                            table[d] = True
                            for e in range(0,10):
                            	if not table[e]:
                            		table[e] = True
                            		for f in range(0,10):
                            			if not table[f]:
                            				table[f] = True
                            				for g in range(0,10):
                            					if not table[g]:
                            						table[g] = True
                            						for h in range(0,10):
                            							if not table[h]:
                            								table[h] = True
                            								for i in range(0,10):
                            									if not table[i]:
                            										table[i] = True
                            										for j in range(0,10):
                            											if not table[j]:
                            												print a,b,c,d,e,f,g,h,i,j
                            												count = count + 1
                            												if count == 1000000:
                            													print a,b,c,d,e,f,g,h,i,j
                            													sys.exit(0)
                            												table[j] = False
                            										table[i] = False
                            								table[h] = False		
                            						table[g] = False
                            				table[f] = False				                            					
                            		table[e] = False		                            			
                            table[d] = False		                            	
                    table[c] = False
            table[b] = False
