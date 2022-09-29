#include <cmath>                                                      // abs(), pow()
#include <compare>                                                    // weak_ordering
#include <iomanip>                                                    // quoted()
#include <iostream>
#include <string>
#include <type_traits>                                                // is_floating_point_v, common_type_t
#include <utility>                                                    // move()

#include "GroceryItem.hpp"



/*******************************************************************************
**  Implementation of non-member private types, objects, and functions
*******************************************************************************/
namespace    // unnamed, anonymous namespace
{
  // Avoid direct equality comparisons on floating point numbers. Two values are equal if they are "close enough", which is
  // represented by Epsilon.  Usually, this is a pretty small number, but since we are dealing with money (only two, maybe three
  // decimal places) we can be a bit more tolerant.  Two floating point values are considered equal if they are within EPSILON of
  // each other.
  template< typename T,  typename U >   requires std::is_floating_point_v<std::common_type_t<T, U> >
  constexpr bool floating_point_is_equal( T const lhs,  U const rhs,  double const EPSILON = 1e-4 ) noexcept
  {
    #ifndef STUDENT_TO_DO_REGION
      ///  Write the lines of code that compare two floating point numbers.  Return true when the left hand side (lhs) and the right
      ///  hand side (rhs) are within Epsilon, and false otherwise.
      ///
      ///  See: "Floating point equality" in https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/
      ///
      ///  Hint:  Avoid writing code that looks like this:
      ///           if( some expression that is true ) return the constant "true"
      ///           else                               return the constant "false"
      ///         for example, avoid:
      ///           if (a < b) return true;
      ///           else       return false;
      ///         do this instead:
      ///           return a < b;
      return std::abs( lhs - rhs ) < EPSILON;
    #endif
  }
}    // unnamed, anonymous namespace







/*******************************************************************************
**  Constructors, assignments, and destructor
*******************************************************************************/

// Default and Conversion Constructor
GroceryItem::GroceryItem( std::string productName, std::string brandName, std::string upcCode, double price )
#ifndef STUDENT_TO_DO_REGION
  /// Copying the parameters into the object's attributes (member variables) "works" but is not correct.  Be sure to move the parameters into the object's attributes
  : _upcCode    { std::move( upcCode     ) },                         // Copy-move idiom
    _brandName  { std::move( brandName   ) },                         // Use the constructor initialization list
    _productName{ std::move( productName ) },
    _price {                 price       }
{}                                                                    // Avoid setting values in constructor's body (when possible)
#endif




// Copy constructor
GroceryItem::GroceryItem( GroceryItem const & other )
#ifndef STUDENT_TO_DO_REGION
  = default;
#endif




// Move constructor
GroceryItem::GroceryItem( GroceryItem && other ) noexcept
#ifndef STUDENT_TO_DO_REGION
  = default;
#endif




// Copy Assignment Operator
GroceryItem & GroceryItem::operator=( GroceryItem const & rhs ) &
#ifndef STUDENT_TO_DO_REGION
  = default;
#endif




// Move Assignment Operator
GroceryItem & GroceryItem::operator=( GroceryItem && rhs ) & noexcept
#ifndef STUDENT_TO_DO_REGION
  = default;
#endif



// Destructor
GroceryItem::~GroceryItem() noexcept
#ifndef STUDENT_TO_DO_REGION
  = default;
#endif








/*******************************************************************************
**  Accessors
*******************************************************************************/

// upcCode() const
std::string const & GroceryItem::upcCode() const &
{
  #ifndef STUDENT_TO_DO_REGION
    return _upcCode;
  #endif
}




// brandName() const
std::string const & GroceryItem::brandName() const &
{
  #ifndef STUDENT_TO_DO_REGION
    return _brandName;
  #endif
}




// productName() const
std::string const & GroceryItem::productName() const &
{
  #ifndef STUDENT_TO_DO_REGION
    return _productName;
  #endif
}



// price() const
double GroceryItem::price() const &
{
  #ifndef STUDENT_TO_DO_REGION
    return _price;
  #endif
}




// upcCode()
std::string GroceryItem::upcCode() &&
{
  #ifndef STUDENT_TO_DO_REGION
    return std::move( _upcCode );
  #endif
}




// brandName()
std::string GroceryItem::brandName() &&
{
  #ifndef STUDENT_TO_DO_REGION
    return std::move( _brandName );
  #endif
}




// productName()
std::string GroceryItem::productName() &&
{
  #ifndef STUDENT_TO_DO_REGION
    return std::move( _productName );
  #endif
}








/*******************************************************************************
**  Modifiers
*******************************************************************************/

// upcCode()
GroceryItem & GroceryItem::upcCode( std::string newUpcCode ) &
{
  #ifndef STUDENT_TO_DO_REGION
    /// Copy assignment "works" but is not correct.  Be sure to move newUpcCode into _upcCode
    _upcCode = std::move( newUpcCode );
    return *this;
  #endif
}




// brandName()
GroceryItem & GroceryItem::brandName( std::string newBrandName ) &
{
  #ifndef STUDENT_TO_DO_REGION
    _brandName = std::move( newBrandName );
    return *this;
  #endif
}




// productName()
GroceryItem & GroceryItem::productName( std::string newProductName ) &
{
  #ifndef STUDENT_TO_DO_REGION
    _productName = std::move( newProductName );
    return *this;
#endif
}




// price()
GroceryItem & GroceryItem::price( double newPrice ) &
{
  #ifndef STUDENT_TO_DO_REGION
    _price = newPrice;
    return *this;
  #endif
}








/*******************************************************************************
**  Relational Operators
*******************************************************************************/

// operator<=>
std::weak_ordering GroceryItem::operator<=>( const GroceryItem & rhs ) const noexcept
{
  // Design decision:  A very simple and convenient defaulted 3-way comparison operator
  //                         auto operator<=>( const GroceryItem & ) const = default;
  //                   in the class definition (header file) would get very close to what is needed and would allow both the <=> and
  //                   the == operators defined here to be skipped.  The physical ordering of the attributes in the class definition
  //                   would have to be changed (easy enough in this case) but the default directly compares floating point types
  //                   (price) for equality, and that should be avoided, in general. For example, if x and y are of type double,
  //                   then  x < y  is okay but  x == y  is not.  So these (operator<=> and operator==) explicit definitions are
  //                   provided.
  //
  //                   Also, many ordering (sorting) algorithms, like those used in std::map and std::set, require at least a weak
  //                   ordering of elements. operator<=> provides only a partial ordering when comparing floating point numbers.
  //
  // Weak order:       Objects that compare equal but are not substitutable (identical).  For example, since _price can be within
  //                   EPSILON, GroceryItem("ProductName", "BrandName", "UPC", 9.99999) and GroceryItem("ProductName", "BrandName",
  //                   "UPC", 10.00001) are equal but they are not identical.  If you ignore case when comparing strings, as another
  //                   example, GroceryItem("ProductName") and GroceryItem("productName") are equal but they are not identical.
  //
  // See std::weak_ordering    at https://en.cppreference.com/w/cpp/utility/compare/weak_ordering and
  //     std::partial_ordering at https://en.cppreference.com/w/cpp/utility/compare/partial_ordering
  //     The Three-Way Comparison Operator at  http://modernescpp.com/index.php/c-20-the-three-way-comparison-operator
  //     Spaceship (Three way comparison) Operator Demystified https://youtu.be/S9ShnAFmiWM
  //
  //
  // Grocery items are equal if all attributes are equal (or within Epsilon for floating point numbers, like price). Grocery items are ordered
  // (sorted) by UPC code, product name, brand name, then price.

  #ifndef STUDENT_TO_DO_REGION
    if( auto result = _upcCode     <=> rhs._upcCode;     result != 0 ) return result;
    if( auto result = _productName <=> rhs._productName; result != 0 ) return result;
    if( auto result = _brandName   <=> rhs._brandName;   result != 0 ) return result;

    // Avoid _price <=> rhs._price
    //  1) floating point three-way comparison yields a partial ordering, which is not convertible to a weak ordering
    //  2) May use a different epsilon value than function operator==() below
    if( floating_point_is_equal( _price, rhs._price ) ) return std::weak_ordering::equivalent;
    if( _price < rhs._price )                           return std::weak_ordering::less;
    else                                                return std::weak_ordering::greater;
  #endif
}




// operator==
bool GroceryItem::operator==( const GroceryItem & rhs ) const noexcept
{
  // All attributes must be equal for the two grocery items to be equal to the other.  This can be done in any order, so put the
  // quickest and then the most likely to be different first.

  #ifndef STUDENT_TO_DO_REGION
    // Note the order attributes are checked for equality is intentionally different than for inequality above.
    return floating_point_is_equal( _price, rhs._price )              // Programming note:  intentionally uses and relies
           &&        _upcCode     == rhs._upcCode                     //                    on short-circuit boolean algebra
           &&        _brandName   == rhs._brandName
           &&        _productName == rhs._productName;
  #endif
}








/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/

// operator>>
std::istream & operator>>( std::istream & stream, GroceryItem & groceryItem )
{
  #ifndef STUDENT_TO_DO_REGION
    /// A lot can go wrong when reading from streams - no permission, wrong types, end of file, etc. Minimal exception guarantee says
    /// there should be no side affects if an error or exception occurs, so let's do our work in a local object and move it into place
    /// at the end if all goes well.
    ///
    /// This function should be symmetrical with operator<< below.  Read what your write, and write what you read
    GroceryItem workingItem;
    char delimiter = '\0';

    ///
    ///
    /// Assume fields are separated by commas & optional spaces, and string attributes are enclosed with double quotes.  For example:
    ///    UPC Code         | Brand Name | Product Name                                                  | Price
    ///    -----------------+------------+---------------------------------------------------------------+-------
    ///    "00034000020706",  "York",      "York Peppermint Patties Dark Chocolate Covered Snack Size"  ,  12.64
    ///
    ///
    /// Hint:  Use std::quoted to read and write quoted strings.  See
    ///        1) https://en.cppreference.com/w/cpp/io/manip/quoted
    ///        2) https://www.youtube.com/watch?v=Mu-GUZuU31A

    // Programming note:  Except for "char" type objects (e.g., delimiter), the default stream extraction behavior is to skip
    //                    leading whitespace (spaces, tabs, newlines, etc.) when reading the next item in the stream. But the
    //                    default can be changed before this function is called.  To remove the assumption white space is skipped,
    //                    the std::ws manipulator is explicitly used to skip leading whitespace.
    //                    https://en.cppreference.com/w/cpp/io/manip/skipws

    if( stream >> std::ws >> std::quoted( workingItem._upcCode     )   &&   stream >> std::ws >> delimiter   &&   delimiter == ','   &&   // intentionally using contextual conversions from stream to bool and
        stream >> std::ws >> std::quoted( workingItem._brandName   )   &&   stream >> std::ws >> delimiter   &&   delimiter == ','   &&   // short-circuit boolean logic to stop as soon as an error is detected
        stream >> std::ws >> std::quoted( workingItem._productName )   &&   stream >> std::ws >> delimiter   &&   delimiter == ','   &&   // see https://en.cppreference.com/w/cpp/language/implicit_conversion, https://en.cppreference.com/w/cpp/language/operator_logical
        stream >> std::ws >>              workingItem._price  )
    {
      // If all okay, move workingItem into the returned grocery item.  Copying the information also "works" but moving is more
      // efficient. Note this uses GroceryItem's move assignment operator.
      groceryItem = std::move( workingItem );
    }
    else  stream.setstate( std::ios::failbit );


    // As an option, if you don't want to verify the delimiter character is really the comma (effectively reading and ignoring the
    // next non-whitespace character), then:
    //
    //    stream >> std::ws >> std::quoted( workingItem._upcCode     ) >> std::ws >> delimiter
    //           >> std::ws >> std::quoted( workingItem._brandName   ) >> std::ws >> delimiter
    //           >> std::ws >> std::quoted( workingItem._productName ) >> std::ws >> delimiter
    //           >> std::ws >>              workingItem._price;
    //    if( stream ) groceryItem = std::move( workingItem );

    return stream;
  #endif
}




// operator<<
std::ostream & operator<<( std::ostream & stream, const GroceryItem & groceryItem )
{
  #ifndef STUDENT_TO_DO_REGION
    /// This function should be symmetrical with operator>> above.  Read what your write, and write what you read
    ///
    /// Hint:  Brand and product names may have quotes, which need to escaped when printing.  Use std::quoted to read and write quoted strings.  See
    ///        1) https://en.cppreference.com/w/cpp/io/manip/quoted
    ///        2) https://www.youtube.com/watch?v=Mu-GUZuU31A
    const std::string delimiter = ",  ";
    stream << std::quoted( groceryItem.upcCode    () ) << delimiter
           << std::quoted( groceryItem.brandName  () ) << delimiter
           << std::quoted( groceryItem.productName() ) << delimiter
           << groceryItem.price();                                            // Note:  Writing the newline character is intentionally omitted (by convention)

    return stream;
  #endif
}
