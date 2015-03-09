#ifndef MESSAGE_H
#define MESSAGE_H

template<class T>
class Message
{
	public:

			Message()
		{
			mData = NULL;
		}

			Message(T data)
		{
			mData = new T(data);
		}

			Message(const Message& source)
		{
			if (source.mData)
			{
				mData = new T(*(source.mData));
			}
		}

			~Message()
		{
			if (mData)
			{
				delete mData;
				mData = NULL;
			}
		}

		Message& operator=(const Message& source)
		{
			if (this != &source)
			{
				if (mData)
				{
					delete mData;
					mData = NULL;
				}

				mData = new T(*(source.mData));
			}

			return *this;
		}

		bool operator==(const Message& other)
		{
			return (*mData == other.mData);
		}

		bool operator!=(const Message& other)
		{
			return !(this == other);
		}

		T* getData(void) const
		{
			return mData;
		}

		void setData(T data)
		{
			if (!mData)
			{
				mData = new T;
			}

			*mData = data;
		}

	private:

		T*	mData;
};

#endif // MESSAGE_H
