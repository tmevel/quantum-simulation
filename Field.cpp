#include "Field.h"
#include <cmath>
#include <complex>
#include <iostream>
#include <fstream>

using namespace std;


template <class T>
Field<T>::Field(int const& width, int const& length, int const& height, T const& zero, double const& boxPerMeter) : m_width(width),m_length(length),m_height(height),m_zero(zero),m_boxPerMeter(boxPerMeter){
	m_invD_2 = m_boxPerMeter * m_boxPerMeter;
	
	m_grid = new T[m_width*m_length*m_height];
	
	for(int i(0);i<m_width*m_length*m_height;i++){
		m_grid[i] = m_zero;
	}
}

template <class T>
Field<T>::Field(Field<T> const& f){
	m_width = f.m_width;
	m_length = f.m_length;
	m_height = f.m_height;
	m_zero = f.m_zero;
	m_boxPerMeter = f.m_boxPerMeter;
	m_invD_2 = f.m_invD_2;
	
	m_grid = new T[m_width*m_length*m_height];
	
	for(int i(0);i<m_width*m_length*m_height;i++){
		m_grid[i] = f.m_grid[i];
	}
}

template <class T>
Field<T>::~Field(){
	delete[] m_grid;
}

template <class T>
T Field<T>::get(int const& x, int const& y, int const& z) const{
	if(x<0||y<0||z<0||x>=m_width||y>=m_length||z>=m_height){
		return m_zero;
	}else{
		return m_grid[x+m_width*(y+m_length*z)];
	}
}

template <class T>
void Field<T>::set(int const& x, int const& y, int const& z, T const& val){
	if(x<0||y<0||z<0||x>=m_width||y>=m_length||z>=m_height){
		return;
	}else{
		m_grid[x+m_width*(y+m_length*z)] = T(val);
	}
}

template <class T>
int Field<T>::width() const{
	return m_width;
}

template <class T>
int Field<T>::length() const{
	return m_length;
}

template <class T>
int Field<T>::height() const{
	return m_height;
}

template <class T>
int Field<T>::boxPerMeter() const{
	return m_boxPerMeter;
}

template <class T>
Field<T> Field<T>::laplacian() const{
	Field<T> lap(m_width, m_length, m_height, m_zero, m_boxPerMeter);
	
	for(int i(0);i<m_width;i++){
		for(int j(0);j<m_length;j++){
			for(int k(0);k<m_height;k++){
				T l(m_zero);
				l+= ( get(i+1,j,k)+get(i-1,j,k)-(get(i,j,k)*2.0) ) * m_invD_2;
				l+= ( get(i,j+1,k)+get(i,j-1,k)-(get(i,j,k)*2.0) ) * m_invD_2;
				//l+= ( get(i,j,k+1)+get(i,j,k-1)-(get(i,j,k)*2.0) ) * m_invD_2;
				
				lap.set(i, j, k, l);
			}
		}
	}
	
	return lap;
}

template <class T>
void Field<T>::write() const{
	for(int k(0);k<m_height;k++){
		cout<<"============"<<endl;
		cout<<"layer n°"<<k<<endl;
		cout<<"------------"<<endl;
		for(int j(0);j<m_length;j++){
			for(int i(0);i<m_width;i++){
				cout<<get(i,j,k)<<" ";
			}
			cout<<endl;
		}
	}
}

template <class T>
void Field<T>::write(string const& filename) const{
	
	ofstream file;
	file.open(filename);
	
	file<<m_width<<" "<<m_length<<" "<<m_height<<endl;
	
	for(int k(0);k<m_height;k++){
		for(int j(0);j<m_length;j++){
			for(int i(0);i<m_width;i++){
				file<<get(i,j,k)<<" ";
			}
		}
	}
	
	file.close();
}

template <class T>
Field<T>& Field<T>::operator+=(Field<T> const& val){
	for(int i(0);i<m_width;i++){
		for(int j(0);j<m_length;j++){
			for(int k(0);k<m_height;k++){
				set(i,j,k, get(i,j,k)+val.get(i,j,k));
			}
		}
	}
	
	return *this;
}

template <class T>
Field<T>& Field<T>::operator-=(Field<T> const& val){
	for(int i(0);i<m_width;i++){
		for(int j(0);j<m_length;j++){
			for(int k(0);k<m_height;k++){
				set(i,j,k, get(i,j,k)-val.get(i,j,k));
			}
		}
	}
	
	return *this;
}

template <class T>
Field<T>& Field<T>::operator*=(T const& val){
	for(int i(0);i<m_width;i++){
		for(int j(0);j<m_length;j++){
			for(int k(0);k<m_height;k++){
				set(i,j,k, get(i,j,k)*val);
			}
		}
	}
	
	return *this;
}

template <class T>
Field<T>& Field<T>::operator/=(T const& val){
	for(int i(0);i<m_width;i++){
		for(int j(0);j<m_length;j++){
			for(int k(0);k<m_height;k++){
				set(i,j,k, get(i,j,k)/val);
			}
		}
	}
	
	return *this;
}

template <class T>
Field<T> Field<T>::operator+(Field<T> const& vrh){
	Field<T> result(*this);
	result+=vrh;
	
	return result;
}

template <class T>
Field<T> Field<T>::operator-(Field<T> const& vrh){
	Field<T> result(*this);
	result-=vrh;
	
	return result;
}

template <class T>
Field<T> Field<T>::operator*(T const& vlh){
	Field<T> result(*this);
	result*=vlh;
	
	return result;
}


template <class T>
Field<T> Field<T>::operator/(T const& vrh){
	Field<T> result(*this);
	result/=vrh;
	
	return result;
}

//template <class T>
//Field<T> operator+(Field<T> const& vlh, Field<T> const& vrh){
	//Field<T> result(vlh);
	//result+=vrh;
	
	//return result;
//}

//template <class T>
//Field<T> operator-(Field<T> const& vlh, Field<T> const& vrh){
	//Field<T> result(vlh);
	//result-=vrh;
	
	//return result;
//}

//template <class T>
//Field<T> operator*(T const& vlh, Field<T> const& vrh){
	//Field<T> result(vrh);
	//result*=vlh;
	
	//return result;
//}

//template <class T>
//Field<T> operator*(Field<T> const& vlh, T const& vrh){
	//return vrh*vlh;
//}

//template <class T>
//Field<T> operator/(Field<T> const& vlh, T const& vrh){
	//Field<T> result(vlh);
	//result/=vrh;
	
	//return result;
//}


template class Field<std::complex<double>>;
template class Field<double>;
template class std::complex<double>;
