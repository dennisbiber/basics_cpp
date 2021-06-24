typedef enum days{SUN, MON, TUE, WED, THU, FRI, SAT} days;

inline days operator++ (days d){
	days x = static_cast<days>((static_cast<int>(d) + 1) % 7); 
	d++;
	return x;
}