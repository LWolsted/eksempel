//Pseudo-random number generation

#include <cstddef> // std::size_t
#include <functional> // std::bind, std::ref 
#include <iostream>
#include <random>

int main() {
	const auto seed = 1;
	
	using Engine = std::mt19937; // Random number engine. Har en periode på 2^(19937)-1 før den gentager sig
	Engine omega(seed); // Engine er en type
    
	std::cout << "omega() = " << omega() << "\n"; // Output herfra vil aldrig ændre sig (medmindre vi ændrer seed, selvfølgelig)
//}
	using Normal = std::normal_distribution<>; // Random number distribution: Gaussian
	Normal Z(0, 1); // standard normal
	
	std::cout << "Z(omega) = " << Z(omega) << "\n"; // Draw a realization (stokastisk variat)
	
	auto z = std::bind(Z, std::ref(omega)); // Create a realization (random number) generator 'z' by binding (by reference) Z's argument to 'omega'
	
	std::cout << "z = " << z() << "\n"; // Draw a realization. Notationen "z()" svarer til "Z(omega)".
//}
	std::size_t M = 10; // Create a vector of doubles 'x', initially with size of M (elements)
	std::vector<double> x(M); // x er pt. en vektor med 10 0-indgange.
	
	for (auto & x_m : x) x_m = z(); // Udskift 0'erne i x med z-realisationer
	
	std::cout << "x: \n"; // Print out vector 'x' and its size
	for (auto x_m : x) std::cout << x_m << " "; 
	endl(std::cout);
	std::cout << "x.size() = " << x.size() << "\n";
//}	
	for (std::size_t i = 0; i != 5; ++i) x.emplace_back(z()); // Udvid x med fem indgange, som skal komme efter de ti første
	
	std::cout << "x: \n"; // Print out vector 'x' and its size
	for (auto x_m : x) std::cout << x_m << " "; endl(std::cout);
	std::cout << "x.size() = " << x.size() << "\n";
	
	return 0;	
}
