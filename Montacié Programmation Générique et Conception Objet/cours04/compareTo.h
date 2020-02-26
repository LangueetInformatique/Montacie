#ifndef COMPARETO_H_
#define COMPARETO_H_

#endif /*COMPARETO_H_*/

// Definition du foncteur binaire de comparaison avec memorisation
template <typename T> class compareTo {
  	private:
  	int res; // memorisation du resultat
  	public:
    int operator () (const T& x, const T& y) {
    	res = x.compareTo(y); 
      return res;
    }
    int get() const {return res;}
  };
