
class Observable(object):
    _properties = {}
    _observers = {}

    @property
    def properties (self):
        return self._properties

    @properties.setter
    def properties (self, value):
        self._properties = value

    def __init__ (self):
        pass

    def __getattr__ (self, attr):
        if attr in self.properties:
            return self.properties[attr]
        else:
            raise AttributeError

    def __setattr__ (self, attr, value):
        self.properties[attr] = value

        if not attr in self._observers:
            self._observers[attr] = []

        for each in self._observers[attr]:
            each.observable_changed (attr, value)

    def attach (self, observer, attr):
        #if not attr in self._observers: return
        if not observer in self._observers[attr]:
            self._observers[attr].append (observer)

    def detach (self, observer, attr):
        try:
            self._observers[attr].remove (observer)
        except:
            raise ValueError

class ObserverOne:
    def observable_changed (self, attr, value):
        print 'observer one', attr, 'changed to', value

class ObserverTwo:
    def observable_changed (self, attr, value):
        print 'observer two', attr, 'changed to', value


if __name__ == '__main__':
    o = Observable ()
    o.love = True
    o.hate = False

    o1 = ObserverOne ()
    o2 = ObserverTwo ()

    o.attach (o1, 'love')
    o.attach (o1, 'hate')
    o.attach (o2, 'love')
    o.attach (o2, 'hate')

    o.love = False
    o.detach (o1, 'hate')
    o.hate = True
