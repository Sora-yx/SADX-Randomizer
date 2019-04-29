#ifndef UTILS_HPP
#define UTILS_HPP

// Utility Functions
#ifdef __cplusplus
// C++ version.

/**
* Get the number of elements in an array.
* @return Number of elements in the array.
*/
template <typename T, size_t N>
static inline size_t LengthOfArray(const T(&)[N])
{
	return N;
}

/**
* Get the size of an array.
* @return Size of the array, in bytes.
*/
template <typename T, size_t N>
static inline size_t SizeOfArray(const T(&)[N])
{
	return N * sizeof(T);
}
#else

// C version.

/**
* Number of elements in an array.
*
* Includes a static check for pointers to make sure
* a dynamically-allocated array wasn't specified.
* Reference: http://stackoverflow.com/questions/8018843/macro-definition-array-size
*/
#define LengthOfArray(x) \
	((int)(((sizeof(x) / sizeof(x[0]))) / \
		(size_t)(!(sizeof(x) % sizeof(x[0])))))

#define SizeOfArray(x) sizeof(x)

#endif

// Macros for functions that need both an array
// and the array length or size.
#define arrayptrandlength(data) data, LengthOfArray(data)
#define arraylengthandptr(data) LengthOfArray(data), data
#define arrayptrandsize(data) data, SizeOfArray(data)
#define arraysizeandptr(data) SizeOfArray(data), data

#endif /* UTILS_HPP */
