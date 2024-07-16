#pragma once

#include <type_traits>
#include <array>
#include <vector>
#include <algorithm>

/*                      Helper template class can be used                           */

template<typename T>
struct convert;

template<typename R, typename...Ts>
struct convert<R(*)(Ts...)> {
	using type = R(Ts...);
};

///////////////////////////////// FIRST TYPE FROM TYPE PACK ///////////////////////////////

template<typename...Ts>
struct first_type;

template<typename T1, typename...Ts>
struct first_type<T1,Ts...> {
	using type = T1;
};

/////////////////////////////// N TH TYPE /////////////////////////////////////////////////////
template<size_t N , typename... Ts>
struct types ;

template<typename T0, typename ...Ts>
struct types<0,T0, Ts...> {
	using type = T0;
};

template<size_t N, typename T0, typename...Ts>
struct types<N, T0, Ts...> {
	using type = typename types<N - 1, Ts...>::type;
};

/* 
         construct a Functor that can overload many functions in one functor
		 Functors F(f1,f2,...,fn);
*/

template<typename F>
struct Functor;

template<typename R, typename ...Ts>
struct Functor<R(*)(Ts...)> {

	Functor(R(*func)(Ts...)) : f{ func } {}

	R operator()(Ts&&...args) {
		return f(std::forward<Ts>(args)...);
	}

	void operator()(R(*function)(Ts...)) {
		f = function;
	}

	typedef R(*function)(Ts...);
	typedef R(types)(Ts...);
	using type_ref = R(&)(Ts...);
	using type = R(Ts...);
private:
	function f;
};

template<typename R, typename ...Ts> 
Functor(R(Ts...)) -> Functor<R(*)(Ts...)>;



// Another definition ------------------------------------------------------------------

template<typename R, typename ...Ts>
struct FUNCTOR {

	FUNCTOR(R(*func)(Ts...)) :f{ func } {}

	R operator()(Ts&&...args) {
		return f(std::forward<Ts>(args)...);
	}


private:
	using typefunc = R(*)(Ts...);
	typefunc f;
};

// MERGE TWO FUNCTION IN ONE OBJECT FUNCTION ---------------------------------------------------------

template<typename F1,typename F2>
struct Functor2F;

template<typename R1, typename ...Ts1,
	     typename R2, typename ...Ts2>
struct Functor2F<R1(Ts1...), R2(Ts2...)> :FUNCTOR<R1,Ts1...>, FUNCTOR<R2,Ts2...> {

	Functor2F(R1(*f1)(Ts1...),R2(*f2)(Ts2...))
		: FUNCTOR< R1, Ts1...>(f1)
		, FUNCTOR< R2, Ts2...>(f2)
	{}

	using  FUNCTOR<R1, Ts1...>::operator();
	using  FUNCTOR<R2, Ts2...>::operator();
};

template<typename R1, typename ...Ts1, typename R2, typename ...Ts2>
Functor2F(R1(*)(Ts1...), R2(*)(Ts2...)) -> Functor2F< R1(Ts1...), R2(Ts2...)>;

// New class of functor DEF 3 -------------------------------------------------------------

template<typename R,typename...Ts>
class functor {
public:

	functor(R(*f1)(Ts...)): f{f1} {}
	
	R operator()(Ts&&...args) {
		return f(std::forward<Ts>(args)...);
	}
	//using F::operator();

private:
	using type_f = R(*)(Ts...);
	type_f  f;
};

/////////////////////////////////// VARIADIC FUNCTOR MERGES ////////////////////////////////

template<typename ...Fs>
struct functors : Functor<Fs>...{

	
	functors(Fs...fs):Functor<Fs>(fs)...{}

	using Functor<Fs>::operator()...;
};

template<typename...Ts>
functors(Ts...)->functors<typename Functor<Ts>::function...>;

///////////////////////// Variadic to put some type function in one vector ///////////////////

template<typename Fs>
struct FunctorVector {

	template<typename...Fs>
	FunctorVector(Fs...fs) {
		int dummy[] = { (functions.push_back(Functor<Fs>(fs)), 0)... };
	}

	auto operator[](int i) {
		return functions[i];
	}

	size_t size() const {
		return functions.size();
	}

	void operator()(Fs f) {
		functions.push_back(Functor<Fs>(f));
	}

private:

	std::vector<Functor<Fs>> functions;
};

template<typename... Fs>
FunctorVector(Fs...) -> FunctorVector<typename first_type<Fs...>::type>;

/// we make one for array fixed length 

template<typename... Fs>
struct FunctorArray {

	using type_f = first_type<Fs...>::type;

	FunctorArray(Fs&...fs) :functions{((void*)&fs)...} {}

	type_f* operator[](size_t n) { return (type_f*)functions[n]; }

private:
	std::array<void*, sizeof...(Fs)> functions;
};

// making array of deferent function

template<typename...Fs>
struct FunctorsArray {

	FunctorsArray(Fs& ...fs):functions{((void*)&fs)...} {}

	template<size_t N>
	typename types<N, Fs...>::type* operator()() { return (typename types<N, Fs...>::type*)functions[N]; }
private:

	std::array<void*, sizeof...(Fs)> functions;

	/*struct Types {
		template<size_t N>
		using type = typename types<N, Ts...>::type;
	};

	std::array<Types, sizeof...(Fs)> arrayTypes;*/

	
};

// comparaison condition and monotonic is as we know 
// if x < y than f(x) < f(y) ; other wise f(x) > f(y);
// F(x,y,f) = { xRy && f(x) R f(y) }

template<typename T, typename Function, typename Comparaison>
auto F( Function f, Comparaison comp) {

	

	return +[](const T& x, const T& y)->bool { comp(x, y) && comp(f(x), f(y)); };

}

float f(int x) { return 100.f / float(x + 10); }

template<typename T>
bool comp(T x, T y) { return x < y; }

// Function type 

template<typename R, typename...Ts>
using Function = R(*)(Ts...);

template<typename R, typename ...Ts>
using Function2 = R(Ts...);

template<typename R, typename...Ts>
using Function3 = R (Ts...);
