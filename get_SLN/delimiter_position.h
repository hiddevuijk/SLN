#ifndef GUARD_delimiter_position_h
#define GUARD_delimiter_position_h


std::vector<int> find_char(std::string str, char ch) {
	std::vector<int> vec;
	for(int i=0;i<str.size();i++) {
		if(str[i] == ch) {
			vec.push_back(i);
		}
	}
	return vec;
}



#endif

