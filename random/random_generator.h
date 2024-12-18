//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Author    : KADDA AOUES.
//                                   Title     : random_generator
//                                   Date      : ?? / ?? / 2023
//                                   Licence   : Under licence of author.
//                                   Namespace : RNG
//                                   RANDOM NUMBER GENERATORS , RNG.    
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <random>
#include <type_traits>
#include <limits>

template<typename T>
using Pair = std::pair<T, T>;

namespace  RNG {

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//         RG RANDOM GENERATOR OF NUMBER INTEGER AND FLOATING POINT
	//         1. BY DEFAULT INT AND FLOAT 
	//         2. CONSTRUCTOR (MIN AND MAX ) FOR BOTH, INT AND FLOATING , BY USING CONVERSION
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Type = void>
	class RG { 
		static_assert(std::is_arithmetic_v<Type>, "Type should be arithmetic type");
		using T = typename std::conditional<std::is_integral_v<Type>, Type, int>::type;
		using F = typename std::conditional<std::is_floating_point_v<Type>, Type, float>::type;

		static std::random_device rdevice;
		std::mt19937 engine;
		std::uniform_int_distribution<T> uiRand;
		std::uniform_real_distribution<F> ufRand;

	public:
		RG(T min, T max) 
			: engine(rdevice()) ,
			  uiRand{ std::uniform_int_distribution<T>(min, max)  } ,
			  ufRand{ std::uniform_real_distribution<F>( static_cast<F>(min), static_cast<F>(max)) }
		{}

		RG(F min, F max) 
			: engine(rdevice()),
			  ufRand{ std::uniform_real_distribution<F>(min, max) },
			  uiRand{ std::uniform_int_distribution<T>(static_cast<T>(min), static_cast<T>(max)) }
		{}

		T operator () ( ) {
			return uiRand(engine);
		}

		F operator () ( F ) {
			return ufRand(engine);
		}

		auto rand() {
			if constexpr (std::is_integral_v<Type>) {
				return uiRand(engine);
			}
			else {
				return ufRand(engine);
			}
		}

		void setRange(T min, T max) {
			uiRand = std::uniform_int_distribution<T>(min, max);
			ufRand = std::uniform_real_distribution<F>(static_cast<F>(min), static_cast<F>(max));
		}

		void setRange(F min, F max) {
			ufRand = std::uniform_real_distribution<T>(min, max);
			uiRand = std::uniform_int_distribution<F>(static_cast<T>(min), static_cast<T>(max));
		}


	};

	template<typename T>
	std::random_device  RG<T>::rdevice;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//                      specialization fo character random variable;
	//                      operator() get random char between min and max;
	//                      operator[] get random index in string value initialized.
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<>
	class RG<char> {

		std::random_device rd;
		std::mt19937 engine;
		std::uniform_int_distribution<int> CharRand;
		std::string m_alpha;

	public:
		RG():RG(CHAR_MIN,CHAR_MAX){}

		RG(char min, char max) 
			: engine(rd())
			, CharRand{ std::uniform_int_distribution<int>{ min,max } }
		{}

		RG(const std::string& Alphabet)
			: engine(rd())
			, m_alpha{Alphabet}
			, CharRand { std::uniform_int_distribution<int>{0,(int)Alphabet.size() - 1}}
		{}

		char operator() () {
			return static_cast<char>(CharRand(engine));
		}

		char operator[](int) {
			return m_alpha[CharRand(engine)];
		}

		void operator[](const std::string& NewStr) {
			m_alpha = NewStr;
		}

		char rand() {
			return operator()();
		}

	};

	// specialization for unsigned charactere
	template<>
	class RG<unsigned char> {

		std::random_device rd;
		std::mt19937 engine;
		std::uniform_int_distribution<int> CharRand;

	public:
		RG():RG(0,UCHAR_MAX) {}

		RG(unsigned char min, unsigned char max) 
			: engine(rd()) 
		    , CharRand{ std::uniform_int_distribution<int>{min,max}}
		{}

		unsigned char operator() () {
			return static_cast<unsigned char>(CharRand(engine));
		}

		auto rand() {
			return operator()();
		}

	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//              SIMPLE RANDOM NUMBER FUNCTOR GENERATOR.
	//              1. INTEGER VALUE  iRG.
	//              2. FLOAT VALUE    fRG.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class iRG {
		static_assert(std::is_integral<T>::value, "T type should be integer type");
		std::random_device               rd;
		std::mt19937                     engine;
		std::uniform_int_distribution<T> iRand;

	public:
        iRG(): engine(rd()){}

		T operator () (T min, T max) {
			if (min > max) std::swap(min, max);
			iRand = std::uniform_int_distribution<T>(min, max);
			return iRand(engine);
		}

	};


	template<typename T>
	class fRG {
		static_assert(std::is_floating_point<T>::value, "T type should be floating point type");
		std::random_device rd;
		std::mt19937 engine;
		std::uniform_real_distribution<T> fRand;

	public:
		fRG() : engine(rd()) {}

		T operator () (T min, T max) {
			if (min > max) std::swap(min, max);
			fRand = std::uniform_real_distribution<T>(min, max);
			return fRand(engine);
		}
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    copyable class like random_device.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Random {

		std::string _rand_name;

	public:
		using result_type = unsigned int;

		Random() {}

		explicit Random(const std::string_view& name) :_rand_name{ name } {}

		_NODISCARD static constexpr result_type(min)() {
			return 0;
		}

		_NODISCARD static constexpr result_type(max)() {
			return static_cast<result_type>(-1);
		}

		_NODISCARD double entropy() const noexcept {
			return 32.0;
		}

		_NODISCARD result_type operator()() {
			return std::_Random_device();
		}

		_NODISCARD std::string name() const noexcept {
			return _rand_name;
		}

		_NODISCARD static result_type rand() {
			return std::_Random_device();
		}
	};

}

namespace rng = RNG;

