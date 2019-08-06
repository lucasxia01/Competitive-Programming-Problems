#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Trie.h"
#include <utility>
#include <algorithm>

using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    ~GenomeMatcherImpl();
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;
    Trie<DNAMatch> lib;
    unordered_map<string, Genome*> genomes;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
}

GenomeMatcherImpl::~GenomeMatcherImpl()
{
    for (unordered_map<string, Genome*>::iterator it = genomes.begin(); it != genomes.end(); it++) {
        delete it->second;
    }
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    string seq;
    genome.extract(0, genome.length(), seq);
    genomes.insert(make_pair(genome.name(), new Genome(genome.name(), seq)));
    for (int i = 0; i + m_minSearchLength <= genome.length(); i++) {
        genome.extract(i, m_minSearchLength, seq);
        DNAMatch dm;
        dm.genomeName = genome.name();
        dm.length = m_minSearchLength;
        dm.position = i;
        lib.insert(seq, dm);
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    matches.clear();
    if (fragment.length() < minimumLength || minimumLength < m_minSearchLength) return false;
    // find the matches
    vector<DNAMatch> allMatches;
    allMatches = lib.find(fragment.substr(0, m_minSearchLength), exactMatchOnly); // O(F^2)
    int diff;
    DNAMatch temp;
    unordered_map<string, DNAMatch> bestMatches;
    for (int i = 0; i < allMatches.size(); i++) { // O(H)
        diff = 0;
        std::string str;
        genomes.at(allMatches[i].genomeName)->extract(allMatches[i].position, m_minSearchLength, str); // O(F)
        if (str == fragment.substr(0, m_minSearchLength) && !exactMatchOnly) diff = 1; // O(F)
        temp = allMatches[i];
        int j = temp.position + m_minSearchLength;
        genomes.at(temp.genomeName)->extract(0, genomes.at(temp.genomeName)->length(), str);
        while (j < temp.position + fragment.length() && j < genomes.at(temp.genomeName)->length()) {
            if (str[j] != fragment[j - temp.position]) { // O(F)
                if (diff) diff--;
                else break;
            }
            j++;
        }
        if (j - temp.position >= minimumLength) {
            temp.length = j - temp.position;
            if (!bestMatches.count(temp.genomeName) || bestMatches[temp.genomeName].length < temp.length) {
                bestMatches[temp.genomeName] = temp;
            }
        }
    }
    for (unordered_map<string, DNAMatch>::iterator it = bestMatches.begin(); it != bestMatches.end(); it++) {
        matches.push_back((*it).second);
    }
    if (matches.size() == 0) return false;  // This compiles, but may not be correct
    return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < m_minSearchLength) return false;
    string seq;
    results.clear();
    vector<DNAMatch> matches;
    unordered_map<string, int> counts;
    for (int i = fragmentMatchLength; i <= query.length(); i+= fragmentMatchLength) { // O(Q)
        query.extract(i - fragmentMatchLength, fragmentMatchLength, seq); // O(F)
        findGenomesWithThisDNA(seq, fragmentMatchLength, exactMatchOnly, matches); // O(HF)
        for (int j = 0; j < matches.size(); j++) { // O(F) worst case
            if (!counts.count(matches[j].genomeName)) counts.insert(make_pair(matches[j].genomeName, 1)); // O(1)
            else counts[matches[j].genomeName]++;
        }
    }
    GenomeMatch temp;
    vector<pair<double, string>> temp2;
    for (unordered_map<string, int>::iterator it = counts.begin(); it != counts.end(); it++) {
        temp2.push_back(make_pair((double) it->second / (query.length() / fragmentMatchLength), it->first));
    }
    sort(temp2.rbegin(), temp2.rend()); // O(HlogH) , H ~= F
    for (int i = 0; i < temp2.size(); i++) {
        temp.genomeName = temp2[i].second;
        temp.percentMatch = 100 * temp2[i].first;
        if (temp.percentMatch < matchPercentThreshold) continue;
        results.push_back(temp);
    }
    if (results.size() == 0) return false;
    return true;
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
