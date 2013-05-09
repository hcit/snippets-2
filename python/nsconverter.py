#        A python module to convert number system by Thura Hlaing
#        Although most of the avalabile OS comes with a calculator, Number System Conversion in those calculators is not satisfactory.
#        None of them support floating point conversion for number systems.
#        But, this module can convert number system (With Floating Point Support) well as far as I tested ...
#        Conversion from decimal to other systems is not exact for numbers with large floating point, others working perfectly!
#        For suggestion and bugs, mail thurahlaing06@gmail.com
#        GNU/GPL
#	  python nsconverter.py sdist to package
  
from distutils.core import setup
setup(name='Number System Converter',
      version='1.0',
      author='thurahlaing06@gmail.com',
      )


"""This Module takes a number string (binary,decimal...)\nAnd convert it to another number system (binary,decimal...)"""

#dictionaries to convert binary to/from octal and hexdecimal System
dictob = {'0':'000','1':'001','2':'010','3':'011','4':'100','5':'101','6':'110','7':'111'}
dictbo = {'000':'0','001':'1','010':'2','011':'3','100':'4','101':'5','110':'6','111':'7'}
dicthb = {'0':'0000','1':'0001','2':'0010','3':'0011','4':'0100','5':'0101','6':'0110','7':'0111','8':'1000','9':'1001','A':'1010','B':'1011','C':'1100','D':'1101','E':'1110','F':'1111'}
dictbh = {'0000':'0','0001':'1','0010':'2','0011':'3','0100':'4','0101':'5','0110':'6','0111':'7','1000':'8','1001':'9','1010':'A','1011':'B','1100':'C','1101':'D','1110':'E','1111':'F'}
accuracy = 20 #Accuracy Settings is for converting decimal to other systems, should be greater than 10  based on your number

def b2d(b):
    """Take a binary string and return a decimal string"""
    #For Tracing, Uncomment print
    try:
        if b.find('.') == -1:
            #if the binary is not a floating point value ...
            d = 0
            tmp = 0
            for i in b:
                d = d + (int(b[-(tmp+1)])) *math.pow(2,tmp)
                tmp = tmp + 1
                #print  tmp, i, d
            return d
        else:
            #if the binary is a floating point value ...
            p = b.find('.')
            bi = b[:p]    # set bi the interger part( before '.')
            bf = b[(p+1):]    #set bf for the floating part( after '.')
            #print bi,bf
            diTemp = 0
            dfTemp = 0
            tmp = 0
            for i in bi:
                diTemp = diTemp + (int(bi[-(tmp+1)])) *math.pow(2,tmp)
                tmp = tmp + 1
                #print tmp, i, diTemp
            di = str(diTemp)    #Value for decimal integral part( before '.')
            tmp = 0
            for i in bf:
                dfTemp = dfTemp + int(i) * math.pow(2,tmp-1)
                tmp = tmp -1
                #print tmp, i, dfTemp
            df = str(dfTemp)    #Value for decimal floating part( after '.')
            m = di.find('.')
            n = df.find('.')
            #print m, n, str(di[:m]), str(df[n:])
            d = str(di[:m]) + str(df[n:])
            return d
    except:
        return "Input cannot contain other than 0 --> 1"


def d2b(d):
    """"Take a decimal string and return a binary string"""           
    #For tracing uncomment print
    try:
        if d.find('.') == -1:
            #if the decimal is not floating point value
            b=[]
            tmp = int(d)
            while tmp != 0:
                b.append(tmp%2)
                tmp = int(tmp/2)
                #print tmp,b
            b.reverse()   
            return "".join([str(i) for i in b])
        else:
            p = d.find('.')
            di = d[:p]        #Decimal integral Value ( before '.')
            df = d[(p+1):]    #Decimal floating Value ( after  '.')
            bi = []
            biTemp =[]
            bf = []
            tmp = int(di)
            while tmp != 0:
                bi.append(tmp%2)
                tmp = int(tmp/2)
                #print tmp,bi
            bi.reverse()
            tmp = float('.'+df)
            tmp = tmp * 2
            while len(bf)< accuracy and tmp != 0:
                strBuff = str(tmp)
                if strBuff[0] == '1':
                    bf.append(1)
                    tmp = float(strBuff[1:]) *2
                    #print strBuff,"*2 = ",tmp,bf
                else:
                    bf.append(0)
                    tmp = tmp *2
                    #print strBuff,"*2 = ",tmp,bf
            b = "".join([str(i) for i in bi]) + "." + "".join([str(i) for i in bf])   
            return b
    except:
        return "Input cannot contain other than 0 --> 9"

def o2b(o):
    """Take an octal string and return a binary string"""           
    b = []
    try:
        for i in o:
            if(i=='.'):
                b.append('.')
            else:
                b.append(dictob[i])
        return "".join([str(i) for i in b])   
    except:
        return "Input cannot contain other than 0 --> 7"
       
def h2b(h):
    """Take a hexadecimal string and return a binary string"""           
    try:
        b = []
        for i in h:
            if(i=='.'):
                b.append('.')
            else:
                b.append(dicthb[i])
        return "".join([str(i) for i in b])   
    except:
        return "Input cannot contain other than 0 --> 9,A --> F"

def b2o(b):
    """Take a binary string and return an octal string"""
    o = []
    try:
        if b.find('.') == -1:
            if len(b) == 1:
                o.append(dictbo['00'+(b[0])])
            elif len(b) == 2:
                o.append(dictbo['0'+(b[-2:])])
            else:
                o.append(dictbo[(b[-3:])])
            for i in range(-3,-len(b),-3):
                if((len(b)+i)==2):
                    o.append(dictbo['0'+(b[i-3:i])])
                elif((len(b)+i)==1):
                    o.append(dictbo['00'+(b[i-3:i])])
                else:   
                    o.append(dictbo[(b[i-3:i])])
            o.reverse()
            return "".join([str(i) for i in o])
        else:
            p = b.find('.')
            bi = b[:p]
            bf = b[(p+1):]
            oi = []
            of = []
            if len(bi) == 1:
                oi.append(dictbo['00'+(bi[0])])
            elif len(bi) == 2:
                oi.append(dictbo['0'+(bi[-2:])])
            else:
                oi.append(dictbo[(bi[-3:])])
            for i in range(-3,-len(bi),-3):
                if((len(bi)+i)==2):
                    oi.append(dictbo['0'+(bi[i-3:i])])
                elif((len(bi)+i)==1):
                    oi.append(dictbo['00'+(bi[i-3:i])])
                else:   
                    oi.append(dictbo[(bi[i-3:i])])
            oi.reverse()
            if len(bf) == 1:
                of.append(dictbo[(bf[0]) + '00'])
            elif len(bf) == 2:
                of.append(dictbo[(bf[:2]) + '0'])
            else:
                of.append(dictbo[(bf[:3])])
            for i in range(3,len(bf),3):
                if len(bf)-i == 2:
                    of.append(dictbo[bf[i:] +'0' ])
                elif len(bf)-i == 1:
                    of.append(dictbo[bf[i:] +'00'])
                else:   
                    of.append(dictbo[bf[i:i+3]])
            o = "".join([str(i) for i in oi]) + "." + "".join([str(i) for i in of])   
            return o           
    except:
        return "Input cannot contain other than 0 --> 1"
       
def b2h(b):
    """Take a binary string and return a hexadecimal string"""           
    h = []
    try:
        if b.find('.') == -1:
            #if the binary is not a floating point value
            if len(b) == 1:
                h.append(dictbh['000'+(b[0])])
            elif len(b) == 2:
                h.append(dictbh['00'+(b[-2:])])
            elif len(b) == 3:
                h.append(dictbh['0'+(b[-3:])])
            else:
                h.append(dictbh[(b[-4:])])
            for i in range(-4,-len(b),-4):
                if((len(b)+i)==3):
                    h.append(dictbh['0'+(b[i-3:i])])
                elif((len(b)+i)==2):
                    h.append(dictbh['00'+(b[i-3:i])])
                elif((len(b)+i)==1):   
                    h.append(dictbh['000'+(b[i-3:i])])
                else:
                    h.append(dictbh[(b[i-4:i])])
            h.reverse()
            return "".join([str(i) for i in h])
        else:
            p = b.find('.')
            bi = b[:p]
            bf = b[p+1:]
            hi = []
            hf = []
            if len(bi) == 1:
                hi.append(dictbh['000'+(bi[0])])
            elif len(bi) == 2:
                hi.append(dictbh['00'+(bi[-2:])])
            elif len(bi) == 3:
                hi.append(dictbh['0'+(bi[-3:])])
            else:
                hi.append(dictbh[(bi[-4:])])
            for i in range(-4,-len(bi),-4):
                if len(bi)+i==3:
                    hi.append(dictbh['0'+(bi[i-3:i])])
                elif len(bi)+i==2:
                    hi.append(dictbh['00'+(bi[i-3:i])])
                elif len(bi)+i==1:   
                    hi.append(dictbh['000'+(bi[i-3:i])])
                else:
                    hi.append(dictbh[(bi[i-4:i])])
            hi.reverse()
            if len(bf) == 1:
                hf.append(dictbh[(bf[0]) + '000'])
            elif len(bf) == 2:
                hf.append(dictbh[(bf[:2]) + '00'])
            elif len(bf) == 3:
                hf.append(dictbh[bf[:3] + '0'])
            else:
                hf.append(dictbh[(bf[:4])])
            for i in range(4,len(bf),4):
                if len(bf)-i == 3:
                    hf.append(dictbh[bf[i:] +'0' ])
                elif len(bf)-i == 2:
                    hf.append(dictbh[bf[i:] +'00'])
                elif len(bf)-i == 1:
                    hf.append(dictbh[bf[i:] +'000'])
                else:   
                    hf.append(dictbh[bf[i:i+4]])
            h = "".join([str(i) for i in hi]) + "." + "".join([str(i) for i in hf])   
            return h                       
    except:
        return "Input cannot contain other than 0 --> 1"

       
def d2o(d):
    """Take a decimal string and return an octal string"""           
    return b2o(d2b(d))
   
def o2d(o):
    """Take an octal string and return a decimal string"""           
    return b2d(o2b(o))

def h2o(h):
    """Take a hexadecimal string and return an octal string"""           
    return b2o(h2b(h))

def o2h(o):
    """Take an octal string and return a hexadecimal string"""           
    return b2h(o2b(o))

def h2d(h):
    """Take a hexadecimal string and return a decimal string"""           
    return b2d(h2b(h))

def d2h(d):
    """Take a decimal string and return a hexadecimal string"""           
    return b2h(d2b(d))

if __name__ == "__main__":
    print __doc__
