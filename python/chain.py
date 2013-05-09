from sys import stdout, stderr

class Printer (object):
    def log (self):
        if 'nxt' in self.__dict__:
            self.nxt.log ()

    def chain (self, nxt):
        self.nxt = nxt
        return nxt

class StdoutPrinter (Printer):
    def log (self):
        stdout.write ("stdout Hello\n")
        super(StdoutPrinter, self).log ()

class StderrPrinter (Printer):
    def log (self):
        stderr.write ("stderr Hello\n")
        super(StderrPrinter, self).log ()

p = StdoutPrinter ()
p.chain (StderrPrinter()) .chain (StdoutPrinter()).chain (StderrPrinter())
