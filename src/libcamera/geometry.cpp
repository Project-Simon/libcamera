/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2019, Google Inc.
 *
 * geometry.cpp - Geometry-related structures
 */

#include <libcamera/geometry.h>

#include <sstream>
#include <stdint.h>

#include <libcamera/base/log.h>

/**
 * \file geometry.h
 * \brief Data structures related to geometric objects
 */

namespace libcamera {

/**
 * \class Point
 * \brief Describe a point in two-dimensional space
 *
 * The Point structure defines a point in two-dimensional space with integer
 * precision. The coordinates of a Point may be negative as well as positive.
 */

/**
 * \fn Point::Point()
 * \brief Construct a Point with x and y set to 0
 */

/**
 * \fn Point::Point(int xpos, int ypos)
 * \brief Construct a Point at given \a xpos and \a ypos values
 * \param[in] xpos The x-coordinate
 * \param[in] ypos The y-coordinate
 */

/**
 * \var Point::x
 * \brief The x-coordinate of the Point
 */

/**
 * \var Point::y
 * \brief The y-coordinate of the Point
 */

/**
 * \brief Assemble and return a string describing the point
 * \return A string describing the point
 */
const std::string Point::toString() const
{
	std::stringstream ss;

	ss << "(" << x << "," << y << ")";

	return ss.str();
}

/**
 * \fn Point Point::operator-() const
 * \brief Negate a Point by negating both its x and y coordinates
 * \return The negated point
 */

/**
 * \brief Compare points for equality
 * \return True if the two points are equal, false otherwise
 */
bool operator==(const Point &lhs, const Point &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

/**
 * \fn bool operator!=(const Point &lhs, const Point &rhs)
 * \brief Compare points for inequality
 * \return True if the two points are not equal, false otherwise
 */

/**
 * \struct Size
 * \brief Describe a two-dimensional size
 *
 * The Size structure defines a two-dimensional size with integer precision.
 */

/**
 * \fn Size::Size()
 * \brief Construct a Size with width and height set to 0
 */

/**
 * \fn Size::Size(unsigned int width, unsigned int height)
 * \brief Construct a Size with given \a width and \a height
 * \param[in] width The Size width
 * \param[in] height The Size height
 */

/**
 * \var Size::width
 * \brief The Size width
 */

/**
 * \var Size::height
 * \brief The Size height
 */

/**
 * \fn bool Size::isNull() const
 * \brief Check if the size is null
 * \return True if both the width and height are 0, or false otherwise
 */

/**
 * \brief Assemble and return a string describing the size
 * \return A string describing the size
 */
const std::string Size::toString() const
{
	return std::to_string(width) + "x" + std::to_string(height);
}

/**
 * \fn Size::alignDownTo(unsigned int hAlignment, unsigned int vAlignment)
 * \brief Align the size down horizontally and vertically in place
 * \param[in] hAlignment Horizontal alignment
 * \param[in] vAlignment Vertical alignment
 *
 * This functions rounds the width and height down to the nearest multiple of
 * \a hAlignment and \a vAlignment respectively.
 *
 * \return A reference to this object
 */

/**
 * \fn Size::alignUpTo(unsigned int hAlignment, unsigned int vAlignment)
 * \brief Align the size up horizontally and vertically in place
 * \param[in] hAlignment Horizontal alignment
 * \param[in] vAlignment Vertical alignment
 *
 * This functions rounds the width and height up to the nearest multiple of
 * \a hAlignment and \a vAlignment respectively.
 *
 * \return A reference to this object
 */

/**
 * \fn Size::boundTo(const Size &bound)
 * \brief Bound the size to \a bound in place
 * \param[in] bound The maximum size
 *
 * This function sets the width and height to the minimum of this size and the
 * \a bound size.
 *
 * \return A reference to this object
 */

/**
 * \fn Size::expandTo(const Size &expand)
 * \brief Expand the size to \a expand
 * \param[in] expand The minimum size
 *
 * This function sets the width and height to the maximum of this size and the
 * \a expand size.
 *
 * \return A reference to this object
 */

/**
 * \fn Size::alignedDownTo(unsigned int hAlignment, unsigned int vAlignment)
 * \brief Align the size down horizontally and vertically
 * \param[in] hAlignment Horizontal alignment
 * \param[in] vAlignment Vertical alignment
 * \return A Size whose width and height are equal to the width and height of
 * this size rounded down to the nearest multiple of \a hAlignment and
 * \a vAlignment respectively
 */

/**
 * \fn Size::alignedUpTo(unsigned int hAlignment, unsigned int vAlignment)
 * \brief Align the size up horizontally and vertically
 * \param[in] hAlignment Horizontal alignment
 * \param[in] vAlignment Vertical alignment
 * \return A Size whose width and height are equal to the width and height of
 * this size rounded up to the nearest multiple of \a hAlignment and
 * \a vAlignment respectively
 */

/**
 * \fn Size::boundedTo(const Size &bound)
 * \brief Bound the size to \a bound
 * \param[in] bound The maximum size
 * \return A Size whose width and height are the minimum of the width and
 * height of this size and the \a bound size
 */

/**
 * \fn Size::expandedTo(const Size &expand)
 * \brief Expand the size to \a expand
 * \param[in] expand The minimum size
 * \return A Size whose width and height are the maximum of the width and
 * height of this size and the \a expand size
 */

/**
 * \brief Bound the size down to match the aspect ratio given by \a ratio
 * \param[in] ratio The size whose aspect ratio must be matched
 *
 * The behaviour of this function is undefined if either the width or the
 * height of the \a ratio is zero.
 *
 * \return A Size whose width and height are equal to the width and height
 * of this Size aligned down to the aspect ratio of \a ratio
 */
Size Size::boundedToAspectRatio(const Size &ratio) const
{
	ASSERT(ratio.width && ratio.height);

	uint64_t ratio1 = static_cast<uint64_t>(width) *
			  static_cast<uint64_t>(ratio.height);
	uint64_t ratio2 = static_cast<uint64_t>(ratio.width) *
			  static_cast<uint64_t>(height);

	if (ratio1 > ratio2)
		return { static_cast<unsigned int>(ratio2 / ratio.height), height };
	else
		return { width, static_cast<unsigned int>(ratio1 / ratio.width) };
}

/**
 * \brief Expand the size to match the aspect ratio given by \a ratio
 * \param[in] ratio The size whose aspect ratio must be matched
 *
 * The behaviour of this function is undefined if either the width or the
 * height of the \a ratio is zero.
 *
 * \return A Size whose width and height are equal to the width and height
 * of this Size expanded up to the aspect ratio of \a ratio
 */
Size Size::expandedToAspectRatio(const Size &ratio) const
{
	ASSERT(ratio.width && ratio.height);

	uint64_t ratio1 = static_cast<uint64_t>(width) *
			  static_cast<uint64_t>(ratio.height);
	uint64_t ratio2 = static_cast<uint64_t>(ratio.width) *
			  static_cast<uint64_t>(height);

	if (ratio1 < ratio2)
		return { static_cast<unsigned int>(ratio2 / ratio.height), height };
	else
		return { width, static_cast<unsigned int>(ratio1 / ratio.width) };
}

/**
 * \brief Center a rectangle of this size at a given Point
 * \param[in] center The center point the Rectangle is to have
 *
 * A Rectangle of this object's size is positioned so that its center
 * is at the given Point.
 *
 * \return A Rectangle of this size, centered at the given Point.
 */
Rectangle Size::centeredTo(const Point &center) const
{
	int x = center.x - width / 2;
	int y = center.y - height / 2;

	return { x, y, width, height };
}

/**
 * \brief Scale size up by the given factor
 * \param[in] factor The factor
 * \return The scaled Size
 */
Size Size::operator*(float factor) const
{
	return Size(width * factor, height * factor);
}

/**
 * \brief Scale size down by the given factor
 * \param[in] factor The factor
 * \return The scaled Size
 */
Size Size::operator/(float factor) const
{
	return Size(width / factor, height / factor);
}

/**
 * \brief Scale this size up by the given factor in place
 * \param[in] factor The factor
 * \return A reference to this object
 */
Size &Size::operator*=(float factor)
{
	width *= factor;
	height *= factor;
	return *this;
}

/**
 * \brief Scale this size down by the given factor in place
 * \param[in] factor The factor
 * \return A reference to this object
 */
Size &Size::operator/=(float factor)
{
	width /= factor;
	height /= factor;
	return *this;
}

/**
 * \brief Compare sizes for equality
 * \return True if the two sizes are equal, false otherwise
 */
bool operator==(const Size &lhs, const Size &rhs)
{
	return lhs.width == rhs.width && lhs.height == rhs.height;
}

/**
 * \brief Compare sizes for smaller than order
 *
 * Sizes are compared on three criteria, in the following order.
 *
 * - A size with smaller width and smaller height is smaller.
 * - A size with smaller area is smaller.
 * - A size with smaller width is smaller.
 *
 * \return True if \a lhs is smaller than \a rhs, false otherwise
 */
bool operator<(const Size &lhs, const Size &rhs)
{
	if (lhs.width < rhs.width && lhs.height < rhs.height)
		return true;
	else if (lhs.width >= rhs.width && lhs.height >= rhs.height)
		return false;

	uint64_t larea = static_cast<uint64_t>(lhs.width) *
			 static_cast<uint64_t>(lhs.height);
	uint64_t rarea = static_cast<uint64_t>(rhs.width) *
			 static_cast<uint64_t>(rhs.height);
	if (larea < rarea)
		return true;
	else if (larea > rarea)
		return false;

	return lhs.width < rhs.width;
}

/**
 * \fn bool operator!=(const Size &lhs, const Size &rhs)
 * \brief Compare sizes for inequality
 * \return True if the two sizes are not equal, false otherwise
 */

/**
 * \fn bool operator<=(const Size &lhs, const Size &rhs)
 * \brief Compare sizes for smaller than or equal to order
 * \return True if \a lhs is smaller than or equal to \a rhs, false otherwise
 * \sa bool operator<(const Size &lhs, const Size &rhs)
 */

/**
 * \fn bool operator>(const Size &lhs, const Size &rhs)
 * \brief Compare sizes for greater than order
 * \return True if \a lhs is greater than \a rhs, false otherwise
 * \sa bool operator<(const Size &lhs, const Size &rhs)
 */

/**
 * \fn bool operator>=(const Size &lhs, const Size &rhs)
 * \brief Compare sizes for greater than or equal to order
 * \return True if \a lhs is greater than or equal to \a rhs, false otherwise
 * \sa bool operator<(const Size &lhs, const Size &rhs)
 */

/**
 * \struct SizeRange
 * \brief Describe a range of sizes
 *
 * A SizeRange describes a range of sizes included in the [min, max] interval
 * for both the width and the height. If the minimum and maximum sizes are
 * identical it represents a single size.
 *
 * Size ranges may further limit the valid sizes through steps in the horizontal
 * and vertical direction. The step values represent the increase in pixels
 * between two valid width or height values, starting from the minimum. Valid
 * sizes within the range are thus expressed as
 *
 *	width = min.width + hStep * x
 *	height = min.height + vStep * y
 *
 *	Where
 *
 *	width <= max.width
 *	height < max.height
 *
 * Note that the step values are not equivalent to alignments, as the minimum
 * width or height may not be a multiple of the corresponding step.
 *
 * The step values may be zero when the range describes only minimum and
 * maximum sizes without implying that all, or any, intermediate size is valid.
 * SizeRange instances the describe a single size have both set values set to 1.
 */

/**
 * \fn SizeRange::SizeRange()
 * \brief Construct a size range initialized to 0
 */

/**
 * \fn SizeRange::SizeRange(const Size &size)
 * \brief Construct a size range representing a single size
 * \param[in] size The size
 */

/**
 * \fn SizeRange::SizeRange(const Size &minSize, const Size &maxSize)
 * \brief Construct a size range with specified min and max, and steps of 1
 * \param[in] minSize The minimum size
 * \param[in] maxSize The maximum size
 */

/**
 * \fn SizeRange::SizeRange(const Size &minSize, const Size &maxSize,
 *			    unsigned int hstep, unsigned int vstep)
 * \brief Construct a size range with specified min, max and step
 * \param[in] minSize The minimum size
 * \param[in] maxSize The maximum size
 * \param[in] hstep The horizontal step
 * \param[in] vstep The vertical step
 */

/**
 * \var SizeRange::min
 * \brief The minimum size
 */

/**
 * \var SizeRange::max
 * \brief The maximum size
 */

/**
 * \var SizeRange::hStep
 * \brief The horizontal step
 */

/**
 * \var SizeRange::vStep
 * \brief The vertical step
 */

/**
 * \brief Test if a size is contained in the range
 * \param[in] size Size to check
 * \return True if \a size is contained in the range
 */
bool SizeRange::contains(const Size &size) const
{
	if (size.width < min.width || size.width > max.width ||
	    size.height < min.height || size.height > max.height ||
	    (hStep && (size.width - min.width) % hStep) ||
	    (vStep && (size.height - min.height) % vStep))
		return false;

	return true;
}

/**
 * \brief Assemble and return a string describing the size range
 * \return A string describing the SizeRange
 */
std::string SizeRange::toString() const
{
	std::stringstream ss;

	ss << "(" << min.toString() << ")-(" << max.toString() << ")/(+"
	   << hStep << ",+" << vStep << ")";

	return ss.str();
}

/**
 * \brief Compare size ranges for equality
 * \return True if the two size ranges are equal, false otherwise
 */
bool operator==(const SizeRange &lhs, const SizeRange &rhs)
{
	return lhs.min == rhs.min && lhs.max == rhs.max;
}

/**
 * \fn bool operator!=(const SizeRange &lhs, const SizeRange &rhs)
 * \brief Compare size ranges for inequality
 * \return True if the two size ranges are not equal, false otherwise
 */

/**
 * \struct Rectangle
 * \brief Describe a rectangle's position and dimensions
 *
 * Rectangles are used to identify an area of an image. They are specified by
 * the coordinates of top-left corner and their horizontal and vertical size.
 *
 * The measure unit of the rectangle coordinates and size, as well as the
 * reference point from which the Rectangle::x and Rectangle::y displacements
 * refers to, are defined by the context were rectangle is used.
 */

/**
 * \fn Rectangle::Rectangle()
 * \brief Construct a Rectangle with all coordinates set to 0
 */

/**
 * \fn Rectangle::Rectangle(int x, int y, const Size &size)
 * \brief Construct a Rectangle with the given position and size
 * \param[in] x The horizontal coordinate of the top-left corner
 * \param[in] y The vertical coordinate of the top-left corner
 * \param[in] size The size
 */

/**
 * \fn Rectangle::Rectangle(int x, int y, unsigned int width, unsigned int height)
 * \brief Construct a Rectangle with the given position and size
 * \param[in] x The horizontal coordinate of the top-left corner
 * \param[in] y The vertical coordinate of the top-left corner
 * \param[in] width The width
 * \param[in] height The height
 */

/**
 * \fn Rectangle::Rectangle(const Size &size)
 * \brief Construct a Rectangle of \a size with its top left corner located
 * at (0,0)
 * \param[in] size The desired Rectangle size
 */

/**
 * \var Rectangle::x
 * \brief The horizontal coordinate of the rectangle's top-left corner
 */

/**
 * \var Rectangle::y
 * \brief The vertical coordinate of the rectangle's top-left corner
 */

/**
 * \var Rectangle::width
 * \brief The distance between the left and right sides
 */

/**
 * \var Rectangle::height
 * \brief The distance between the top and bottom sides
 */

/**
 * \fn bool Rectangle::isNull() const
 * \brief Check if the rectangle is null
 * \return True if both the width and height are 0, or false otherwise
 */

/**
 * \brief Assemble and return a string describing the rectangle
 * \return A string describing the Rectangle
 */
const std::string Rectangle::toString() const
{
	std::stringstream ss;

	ss << "(" << x << "x" << y << ")/" << width << "x" << height;

	return ss.str();
}

/**
 * \brief Retrieve the center point of this rectangle
 * \return The center Point
 */
Point Rectangle::center() const
{
	return { x + static_cast<int>(width / 2), y + static_cast<int>(height / 2) };
}

/**
 * \fn Size Rectangle::size() const
 * \brief Retrieve the size of this rectangle
 * \return The Rectangle size
 */

/**
 * \fn Point Rectangle::topLeft() const
 * \brief Retrieve the coordinates of the top left corner of this Rectangle
 * \return The Rectangle's top left corner
 */

/**
 * \brief Apply a non-uniform rational scaling in place to this Rectangle
 * \param[in] numerator The numerators of the x and y scaling factors
 * \param[in] denominator The denominators of the x and y scaling factors
 *
 * A non-uniform scaling is applied in place such the resulting x
 * coordinates are multiplied by numerator.width / denominator.width,
 * and similarly for the y coordinates (using height in place of width).
 *
 * \return A reference to this object
 */
Rectangle &Rectangle::scaleBy(const Size &numerator, const Size &denominator)
{
	x = static_cast<int64_t>(x) * numerator.width / denominator.width;
	y = static_cast<int64_t>(y) * numerator.height / denominator.height;
	width = static_cast<uint64_t>(width) * numerator.width / denominator.width;
	height = static_cast<uint64_t>(height) * numerator.height / denominator.height;

	return *this;
}

/**
 * \brief Translate this Rectangle in place by the given Point
 * \param[in] point The amount to translate the Rectangle by
 *
 * The Rectangle is translated in the x-direction by the point's x coordinate
 * and in the y-direction by the point's y coordinate.
 *
 * \return A reference to this object
 */
Rectangle &Rectangle::translateBy(const Point &point)
{
	x += point.x;
	y += point.y;

	return *this;
}

/**
 * \brief Calculate the intersection of this Rectangle with another
 * \param[in] bound The Rectangle that is intersected with this Rectangle
 *
 * This function calculates the standard intersection of two rectangles. If the
 * rectangles do not overlap in either the x or y direction, then the size
 * of that dimension in the result (its width or height) is set to zero. Even
 * when one dimension is set to zero, note that the other dimension may still
 * have a positive value if there was some overlap.
 *
 * \return A Rectangle that is the intersection of the input rectangles
 */
Rectangle Rectangle::boundedTo(const Rectangle &bound) const
{
	int topLeftX = std::max(x, bound.x);
	int topLeftY = std::max(y, bound.y);
	int bottomRightX = std::min<int>(x + width, bound.x + bound.width);
	int bottomRightY = std::min<int>(y + height, bound.y + bound.height);

	unsigned int newWidth = std::max(bottomRightX - topLeftX, 0);
	unsigned int newHeight = std::max(bottomRightY - topLeftY, 0);

	return { topLeftX, topLeftY, newWidth, newHeight };
}

/**
 * \brief Enclose a Rectangle so as not to exceed another Rectangle
 * \param[in] boundary The limit that the returned Rectangle will not exceed
 *
 * The Rectangle is modified so that it does not exceed the given \a boundary.
 * This process involves translating the Rectangle if any of its edges
 * lie beyond \a boundary, so that those edges then lie along the boundary
 * instead.
 *
 * If either width or height are larger than \a boundary, then the returned
 * Rectangle is clipped to be no larger. But other than this, the
 * Rectangle is not clipped or reduced in size, merely translated.
 *
 * Note that this is not a conventional Rectangle intersection function
 * which is provided by boundedTo().
 *
 * \return A Rectangle that does not extend beyond a boundary Rectangle
 */
Rectangle Rectangle::enclosedIn(const Rectangle &boundary) const
{
	/* We can't be bigger than the boundary rectangle. */
	Rectangle result = boundedTo(Rectangle{ x, y, boundary.size() });

	result.x = std::clamp<int>(result.x, boundary.x,
				   boundary.x + boundary.width - result.width);
	result.y = std::clamp<int>(result.y, boundary.y,
				   boundary.y + boundary.height - result.height);

	return result;
}

/**
 * \brief Apply a non-uniform rational scaling to this Rectangle
 * \param[in] numerator The numerators of the x and y scaling factors
 * \param[in] denominator The denominators of the x and y scaling factors
 *
 * A non-uniform scaling is applied such the resulting x
 * coordinates are multiplied by numerator.width / denominator.width,
 * and similarly for the y coordinates (using height in place of width).
 *
 * \return The non-uniformly scaled Rectangle
 */
Rectangle Rectangle::scaledBy(const Size &numerator, const Size &denominator) const
{
	int scaledX = static_cast<int64_t>(x) * numerator.width / denominator.width;
	int scaledY = static_cast<int64_t>(y) * numerator.height / denominator.height;
	unsigned int scaledWidth = static_cast<uint64_t>(width) * numerator.width / denominator.width;
	unsigned int scaledHeight = static_cast<uint64_t>(height) * numerator.height / denominator.height;

	return { scaledX, scaledY, scaledWidth, scaledHeight };
}

/**
 * \brief Translate a Rectangle by the given amounts
 * \param[in] point The amount to translate the Rectangle by
 *
 * The Rectangle is translated in the x-direction by the point's x coordinate
 * and in the y-direction by the point's y coordinate.
 *
 * \return The translated Rectangle
 */
Rectangle Rectangle::translatedBy(const Point &point) const
{
	return { x + point.x, y + point.y, width, height };
}

/**
 * \brief Compare rectangles for equality
 * \return True if the two rectangles are equal, false otherwise
 */
bool operator==(const Rectangle &lhs, const Rectangle &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y &&
	       lhs.width == rhs.width && lhs.height == rhs.height;
}

/**
 * \fn bool operator!=(const Rectangle &lhs, const Rectangle &rhs)
 * \brief Compare rectangles for inequality
 * \return True if the two rectangles are not equal, false otherwise
 */

} /* namespace libcamera */
