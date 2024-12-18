#ifndef HISTO_INFO
#define HISTO_INFO

using namespace std;

struct histo_info {
    char letter = '*';
    int frequency = 0;

    bool operator<(const histo_info& other){
        return this->frequency < other.frequency;
    }
    bool operator>(const histo_info& other){
        return this->frequency > other.frequency;
    }
    bool operator<=(const histo_info& other){
        return this->frequency <= other.frequency;
    }
    bool operator>=(const histo_info& other){
        return this->frequency >= other.frequency;
    }
    bool operator==(const histo_info& other){
        return (this->letter = other.letter);
    }
    
};

 ostream& operator << (ostream &stream, const histo_info& hist_inf)  {
        stream << "[" << hist_inf.letter << "  " << hist_inf.frequency << "]";
	    return stream;
    }

#endif