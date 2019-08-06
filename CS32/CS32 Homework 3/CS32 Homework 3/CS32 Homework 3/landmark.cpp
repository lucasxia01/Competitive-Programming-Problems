class Landmark {
public:
    Landmark(string name) {
        m_name = new string(name);
        m_color = new string;
        m_icon = new string;
    }
    virtual ~Landmark() {
        delete m_name;
        delete m_color;
        delete m_icon;
    }
    string color() const {
        return *m_color;
    }
    string icon() const {
        return *m_icon;
    }
    string name() const {
        return *m_name;
    }
    string* getColor() const {
        return m_color;
    }
    string* getIcon() const {
        return m_icon;
    }
    string* getName() const {
        return m_name;
    }
    virtual void useless() const = 0;
private:
    string *m_color, *m_icon, *m_name;
};

class Hotel: public Landmark {
public:
    Hotel(string name) : Landmark(name) {
        
        *getIcon() = "bed";
        *getColor() = "yellow";
    }
    virtual ~Hotel() {
        cout << "Destroying the hotel " << name() << "." << endl;
    }
    virtual void useless() const {}
};

class Restaurant: public Landmark {
public:
    Restaurant(string name, int capacity): Landmark(name) {
        m_capacity = capacity;
        if (m_capacity < 40) *getIcon() = "small knife/fork";
        else *getIcon() = "large knife/fork";
        *getColor() = "yellow";
    }
    virtual ~Restaurant() {
        cout << "Destroying the restaurant " << name() << "." << endl;
    }
    virtual void useless() const {}
private:
    int m_capacity;
};

class Hospital: public Landmark {
public:
    Hospital(string name) : Landmark(name) {
        *getIcon() = "H";
        *getColor() = "blue";
    }
    virtual ~Hospital() {
        cout << "Destroying the hospital " << name() << "." << endl;
    }
    virtual void useless() const {}
};
