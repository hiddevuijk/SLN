#ifndef GUARD_where_in_vec_h
#define GUARD_where_in_vec_h


int where_in_vec(std::string str, std::vector<std::string> vec) {
	for(int i=0;i<vec.size();i++) {
		if(str==vec[i]) return i;
	}
	return -1;
}





#endif


