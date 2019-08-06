#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_nm, m_seq;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    // This compiles, but may not be correct
    m_nm = nm;
    m_seq = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
    if (!genomeSource) return false;
    string name, seq = "", s, valid = "ACTGNactgn";
    getline(genomeSource, s);
    if (s[0] != '>') return false;
    if (s.length() == 1) return false;
    name = s.substr(1);
    while (getline(genomeSource, s)) {
        if (s[0] == '>') {
            if (seq.length() == 0) return false;
            Genome g(name, seq);
            genomes.push_back(g);
            seq = "";
            if (s.length() == 1) return false;
            name = s.substr(1);
        } else {
            if (s.length() > 80 || s.length() < 1) return false;
            for (int i = 0; i < s.length(); i++) if (valid.find(s[i]) == -1) return false;
            seq += s;
        }
    }
    if (seq.length() == 0) return false;
    Genome g(name, seq);
    genomes.push_back(g);
    return true;  // This compiles, but may not be correct
}

int GenomeImpl::length() const
{
    return int(m_seq.length());  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_nm;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position < 0 || position + length > this->length()) return false;
    fragment = m_seq.substr(position, length);
    return true;// This compiles, but may not be correct
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
