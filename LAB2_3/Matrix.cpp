#include <iostream>
#include <iomanip>
#include <time.h>
#include "windows.h"
#include <math.h>
#include "Header.h"
#include <string>


namespace OOP
{
	unsigned matrix::IDS = 0;

	matrix::matrix(unsigned int r, unsigned int c, double(*genMtr)(unsigned int i, unsigned int j)) : matrix()
	{
		if (r > 0 && c > 0)
		{
			this->rows = r;
			this->cols = c;
			mtr = new double[r * c]();

			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
					mtr[i * c + j] = genMtr(i, j);
			}
		}
	}

	matrix::matrix(unsigned int r, unsigned int c) : matrix()
	{
		if (r > 0 && c > 0)
		{
			this->rows = r;
			this->cols = c;
			mtr = new double[r * c]();

			fill(r, c, mtr);
		}
	}

	matrix::matrix(unsigned int s)
	{
		if (s <= 0)
		{
			mtr_id = ++IDS;
			this->rows = NULL;
			this->cols = NULL;
			mtr = nullptr;

			std::cout << "Вызвался конструктор и создалася матрица " << mtr_id << std::endl;
		}
		else
		{
			mtr_id = ++IDS;
			this->rows = s;
			this->cols = s;
			mtr = new double[s * s]();
			fill(s, s, mtr);
			std::cout << "Вызвался конструктор и создалася матрица " << mtr_id << std::endl;
		}
	}

	matrix::~matrix()
	{
		delete[] this->mtr;
		std::cout << "Вызвался деструктор и удалилась матрица " << mtr_id << std::endl;
	}

	matrix::matrix(const matrix& other)
	{
		if (!other.isNULL())
		{
			mtr_id = ++IDS;
			this->rows = other.rows;
			this->cols = other.cols;
			this->mtr = new double[this->rows * this->cols];

			for (int i = 0; i < (this->rows * this->cols); i++)
			{
				this->mtr[i] = other.mtr[i];
			}

			std::cout << "Вызвался конструктор и скопировался объект " << mtr_id << std::endl;
		}
		else
			throw "Ошибка копирования";
	}

	matrix::matrix(matrix&& other)
		:rows(0), cols(0), mtr(nullptr)
	{
		std::swap(rows, other.rows);
		std::swap(cols, other.cols);
		std::swap(mtr, other.mtr);
		mtr_id = ++IDS;
		std::cout << "Вызван конструктор перемещения, объект с номером " << other.mtr_id << " перемещен в объект " << mtr_id << std::endl;
	}

	int matrix::CheckForSum(const matrix& other) const
	{
		return ((this->rows == other.rows) && (this->cols == other.cols));
	}

	int matrix::CheckForMult(const matrix& other) const
	{
		return this->rows == other.cols;
	}

	double matrix::MtrMax() const
	{
		if (!this->isNULL()) {
			double a = mtr[0];
			for (int i = 1; i < this->rows * this->cols; i++)
				if (this->mtr[i] > a)
					a = this->mtr[i];
			return a;
		}
		else
		{
			throw "Нельзя найти минимальный элемент, так как матрица пуста";
		}
	}

	double matrix::MtrMin() const
	{
		if (!this->isNULL()) {
			double a = mtr[0];
			for (int i = 1; i < this->rows * this->cols; i++)
				if (this->mtr[i] < a)
					a = this->mtr[i];
			return a;
		}
		else
		{
			throw "Нельзя найти минимальный элемент, так как матрица пуста";
		}
	}

	bool matrix::isNULL() const
	{
		return mtr == nullptr;
	}

	matrix& matrix::operator=(const matrix& other)
	{
		if (this->rows * this->cols != other.rows * other.cols)
		{
			if (this->mtr != nullptr)
				delete[] this->mtr;
			this->mtr = new double[other.rows * other.cols];
		}
		this->rows = other.rows;
		this->cols = other.cols;

		for (int i = 0; i < (this->rows * this->cols); i++)
		{
			this->mtr[i] = other.mtr[i];
		}

		return *this;
	}

	matrix& matrix::operator=(matrix&& other)
	{
		std::swap(rows, other.rows);
		std::swap(cols, other.cols);
		std::swap(mtr, other.mtr);
		return *this;
	}

	matrix& matrix::operator+=(const matrix& other)
	{
		if (this->CheckForSum(other))
		{ 
			if (!this->isNULL())
			{
				for (int i = 0; i < (this->rows * this->cols); i++)
				{
					this->mtr[i] += other.mtr[i];
				}
				return *this;
			}
			else
				return *this;
		}
		else
		{
			throw "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя складывать!";
		}
	}

	matrix& matrix::operator-=(const matrix& other)
	{
		if (this->CheckForSum(other))
		{
			if (!this->isNULL())
			{
				for (int i = 0; i < (this->rows * this->cols); i++)
				{
					this->mtr[i] -= other.mtr[i];
				}
				return *this;
			}
			else
				return *this;
		}
		else
		{
			throw "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя вычитать!";
		}
	}

	matrix& matrix::operator*=(const double k)
	{
		if (!this->isNULL()) {
			for (int i = 0; i < (this->rows * this->cols); i++)
			{
				this->mtr[i] *= k;
			}
			return *this;
		}
		else
		{
			return *this;
		}
	}

	matrix& matrix::operator*=(const matrix& other)
	{

		if (CheckForMult(other)) {
			if (!this->isNULL())
			{
				double* New = new double[this->rows * other.cols];
				for (int i = 0; i < rows * other.cols; i++)
					New[i] = 0.0;
				for (int i = 0; i < this->rows; ++i)
				{
					for (int j = 0; j < other.cols; ++j)
					{
						for (int k = 0; k < this->cols; ++k)
							New[i * other.cols + j] += (mtr[i * this->cols + k] * other.mtr[k * other.cols + j]);
					}
				}

				delete[] this->mtr;
				cols = other.cols;
				mtr = New;
				return *this;
			}
			else return *this;
		}
		else
		{
			throw "Ошибка! Матрицы с номерами " + std::to_string(mtr_id) + " и " + std::to_string(other.mtr_id) + " нельзя умножать!";
		}
	}

	unsigned int matrix::Get_cols() const
	{
		return this->cols;
	}

	unsigned int matrix::Get_rows() const
	{
		return this->rows;
	}

	std::ostream& operator<<(std::ostream& out, const matrix& other)
	{
		if (!other.isNULL())
		{
			int pl = out.width();
			if (pl == 0)
				pl = 12;
			for (int i = 0; i < other.rows; i++) {
				for (int j = 0; j < other.cols; j++)
					out << std::setw(pl) << other.mtr[i * other.cols + j];
				out << "\n";
			}
			out << "\n";
			return out;
		}
		else
		{
			throw "Ошибка! Матрица с номером " + std::to_string(other.mtr_id) + "пуста!";
		}
	}

	matrix operator+(const matrix& a, const matrix& b)
	{
		return std::move(matrix(a) += b);
	}

	matrix operator-(const matrix& a, const matrix& b)
	{
		return std::move(matrix(a) -= b);
	}

	matrix operator*(const matrix& a, const matrix& b)
	{
		return std::move(matrix(a) *= b);
	}

	matrix operator*(const matrix& a, double k)
	{
		return std::move(matrix(a) *= k);
	}

	matrix::matrixRow matrix::operator[](int ind)
	{
		if (ind <= cols + 1 && ind >= 1)
			return matrixRow(this, ind - 1);
		else
		{
			throw "Ошибка! Выход за границы матрицы объектом с номером " + std::to_string(mtr_id);
		}
	}

	const matrix::matrixRow matrix::operator[](int ind) const {
		if (ind <= cols && ind >= 0)
			return matrixRow(this, ind - 1);
		else
		{
			throw "Ошибка! Выход за границы матрицы объектом с номером " + std::to_string(mtr_id);
		}
	}

	matrix::matrixRow::matrixRow(const matrix* other, unsigned R)
	{
		r = other->rows;
		c = other->cols;
		this->R = R;
		this->mtr = other->mtr;
	}

	double& matrix::matrixRow::operator[](unsigned int ind)
	{
		if (ind <= c + 1 && ind >= 1)
			return mtr[R * c + ind - 1];
		else
		{
			throw "Ошибка! Выход за границы матрицы текущим элементом! ";
		}
	}

	double const matrix::matrixRow::operator[](unsigned int ind) const
	{
		if (ind <= c + 1 && ind >= 1)
			return mtr[R * c + ind - 1];
		else 
		{
			throw "Ошибка! Выход за границы матрицы текущим элементом!";
		}
	}

	void fill(int r, int c, double* mtr)
	{

		for (int i = 0; i < r * c; i++)
			mtr[i] = 1.0 + 98.0 * rand() / (double)RAND_MAX;
	}

	vector::vector(unsigned int r) : matrix(r, 1)
	{
		mtr_id = IDS;
		std::cout << "Вызвался конструктор и создалася вектор " << mtr_id << std::endl;
	}

	vector::vector(unsigned int r, double(*genVec)(unsigned int i)) : matrix(r, 1)
	{
		for (int i = 0; i < r; i++)
			mtr[i] = genVec(i);
		mtr_id = IDS;
		std::cout << "Вызвался конструктор и создался вектор " << mtr_id << std::endl;
	}

	vector::~vector()
	{
		std::cout << "Вызвался деструктор и удалился вектор " << mtr_id << std::endl;
	}

	vector::vector(const matrix& other) : matrix(other)
	{
		if (other.Get_cols() > 1) throw "Ошибка при копировании";
		mtr_id = IDS;
		std::cout << "Вызвался конструктор и скопировался вектор " << mtr_id << std::endl;
	}

	vector::vector(matrix&& other) : matrix(std::move(other))
	{
		if (other.Get_cols() > 1) throw "Ошибка при перемещении";
		mtr_id = IDS;
		std::cout << "Вызвался конструктор и переместился вектор " << mtr_id << std::endl;
	}

	vector& vector::operator=(const matrix& other)
	{
		matrix::operator=(other);
		return *this;
	}

	vector& vector::operator=(matrix&& other)
	{
		matrix::operator=(std::move(other));
		return *this;
	}

	vector& vector::operator+=(const matrix& other)
	{
		matrix::operator+=(other);
		return *this;
	}

	vector& vector::operator-=(const matrix& other)
	{
		matrix::operator-=(other);
		return *this;
	}

	vector& vector::operator*=(const double k)
	{
		matrix::operator*=(k);
		return *this;
	}

	vector& vector::operator*=(const matrix& other)
	{
		matrix::operator*=(other);
		return *this;
	}
	double& vector::operator[](unsigned int ind)
	{
		if (ind <= rows + 1 && ind >= 1)
			return mtr[rows - 1];
		else
		{
			throw "Ошибка! Выход за границы матрицы текущим элементом!";
		}
	}
	double const vector::operator[](unsigned int ind) const
	{
		if (ind <= rows + 1 && ind >= 1)
			return mtr[rows - 1];
		else 
		{
			throw "Ошибка! Выход за границы матрицы текущим элементом!";
		}
	}
}