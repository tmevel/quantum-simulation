#ifndef FIELD_H
#define FIELD_H


#include <string>


template <class T>
class Field{
	public:
	
	Field(int const& width, int const& length, int const& height, T const& zero, double const& boxPerMeter);
	Field(Field<T> const& f);
	~Field();
	
	T get(int const& x, int const& y, int const& z) const;
	void set(int const& x, int const& y, int const& z, T const& val);
	int width() const;
	int length() const;
	int height() const;
	int boxPerMeter() const;
	Field<T> laplacian() const;
	void write() const;
	void write(std::string const& filename) const;
	Field<T>& operator+=(Field<T> const& val);
	Field<T>& operator-=(Field<T> const& val);
	Field<T>& operator*=(T const& val);
	Field<T>& operator/=(T const& val);
	Field<T> operator+ (Field<T> const& vrh);
	Field<T> operator- (Field<T> const& vrh);
	//Field<T> operator* (Field<T> const& vrh);
	Field<T> operator*(T const& vrh);
	Field<T> operator/(T const& vrh);
	
	protected:
	
	int m_width;
	int m_length;
	int m_height;
	T m_zero;
	double m_invD_2;
	double m_boxPerMeter;
	
	private:
	
	T *m_grid;
};

//template <class T>
//Field<T> operator+ (Field<T> const& vlh, Field<T> const& vrh);

//template <class T>
//Field<T> operator- <> (Field<T> const& vlh, Field<T> const& vrh);

//template <class T>
//Field<T> operator* <> (T const& vlh, Field<T> const& vrh);

//template <class T>
//Field<T> operator*(Field<T> const& vlh, T const& vrh);

//template <class T>
//Field<T> operator/(Field<T> const& vlh, T const& vrh);


#endif //FIELD_H_INCLUDED
