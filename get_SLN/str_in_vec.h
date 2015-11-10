#ifndef GUARD_add_h
#define GUARD_add_h

bool str_in_vec(std::string str, std::vector<std::string> vec) {
	bool siv = false;
	for(int i=0;i<vec.size();i++) {
		if(str==vec[i]){
			siv = true;
		}
	}
	return siv;
}

#endif

