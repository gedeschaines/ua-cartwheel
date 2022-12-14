// This file contains all the template instanciations for things needed in Utils

// Instanciate used STL classes
#pragma warning (push)
#pragma warning (disable : 4275 4251 4231)

#include <vector>

namespace CartWheel { namespace Math {

class Observer;

UTILS_TEMPLATE( std::vector<int> )
UTILS_TEMPLATE( std::vector<unsigned int> )
UTILS_TEMPLATE( std::vector<double> )
UTILS_TEMPLATE( std::vector< Observer* > )

}
}
#pragma warning (pop)
