#ifndef SORT_H_ODDERIKF
#define SORT_H_ODDERIKF

namespace my{




template<typename I>
void insertsort( I low, I high ){
	for(auto i = low; i < high; i++){
	auto x = *i;
	for(auto j = i-1; j >= low && *j > x; j--){
		*(j+1) = *j;
	}
	*(low) = x;
	}
}

template <typename L>
bool verify(L& list){
	for(auto i = std::begin(list); i < std::end(list) - 1; i++){
	if (*i > *(i+1)) return false;
	}
	return true;
}

template<typename I>
void quickinsertsort( I low, I high ){
	if (low < high-1) {
		if(std::distance(low,high) < 1<<22) insertsort(low, high);
		else{
		auto lp = low + std::distance(low, high-1)/3;
			auto rp = high-1 - std::distance(low, high-1)/3;
			std::swap(*low, *lp );
			std::swap(*(high-1), *rp );
			lp = low;
			rp = high-1;
			if (*lp > *rp) std::swap(*lp, *rp);
			auto i = lp+1;
			auto j = rp-1;
			auto p = i;
			auto q = j;
			while (i<=j){
			if (*p < *lp) p++;
			else if (*q > *rp) q--;

			else if (*i < *lp && i>p) {
				std::swap(*i, *p);
				p++;
			} else if (*j > *rp && j<q) {
				std::swap(*j, *q);
				q--;
			}
			else if (*i <= *rp) i++;
			else if (*j > *lp) j--;
			else std::swap (*i, *j);
			}
			std::swap(*lp, *(p-1));
			lp = p-1;
			std::swap(*rp, *(q+1));
			rp = q+1;

			doublepivotquicksort(low, lp);
			doublepivotquicksort(lp+1, rp);
			doublepivotquicksort(rp+1, high);
		}
	}
}

template<typename I>
void quicksort( I low, I high ){
	if (low < high) {

	//partition
	auto pivot = low + std::distance(low, high) / 2; //
	std::swap(*low, *pivot);
	pivot = low;
	auto i = pivot+1;
	auto j = high-1;
	while (i<=j){
		if (*i <= *pivot) i++;
		else if (*j > *pivot) j--;
		else std::swap(*i,*j);
	}
	std::swap(*pivot, *(i-1));
	pivot = i-1;

	//recurse
	quicksort(low, pivot);
	quicksort(pivot + 1, high);

	}
}

template<typename I>
void doublepivotquicksort( I low, I high ){
	if (low < high-1) {
	auto lp = low + std::distance(low, high-1)/3;
	auto rp = high-1 - std::distance(low, high-1)/3;
	std::swap(*low, *lp );
	std::swap(*(high-1), *rp );
	lp = low;
	rp = high-1;
	if (*lp > *rp) std::swap(*lp, *rp);
	auto i = lp+1;
	auto j = rp-1;
	auto p = i;
	auto q = j;
	while (i<=j){
		if (*p < *lp) p++;
		else if (*q > *rp) q--;

		else if (*i < *lp && i>p) {
			std::swap(*i, *p);
			p++;
		} else if (*j > *rp && j<q) {
			std::swap(*j, *q);
			q--;
		}
		else if (*i <= *rp) i++;
		else if (*j > *lp) j--;
		else std::swap (*i, *j);
	}
	std::swap(*lp, *(p-1));
	lp = p-1;
	std::swap(*rp, *(q+1));
	rp = q+1;

	doublepivotquicksort(low, lp);
	doublepivotquicksort(lp+1, rp);
	doublepivotquicksort(rp+1, high);
	}
}


}


#endif