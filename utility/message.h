#ifndef BD3GE_MESSAGE_H
#define BD3GE_MESSAGE_H

namespace BD3GE {
	template<class T>
	class Message {
		public:

			Message() {
				m_data = nullptr;
			}

			Message(T data) {
				m_data = new T(data);
			}

			Message(const Message& source) {
				if (source.m_data) {
					m_data = new T(*(source.m_data));
				}
			}

			~Message() {
				delete m_data;
				m_data = nullptr;
			}

			Message& operator=(const Message& source) {
				if (this != &source) {
					delete m_data;
					m_data = nullptr;

					m_data = new T(*(source.m_data));
				}

				return *this;
			}

			bool operator==(const Message& other) {
				return (*m_data == other.m_data);
			}

			bool operator!=(const Message& other) {
				return !(this == other);
			}

			T* get_data(void) const {
				return m_data;
			}

			void set_data(T data) {
				if (!m_data) {
					m_data = new T;
				}

				*m_data = data;
			}

		private:

			T*	m_data;
	};
}

#endif // BD3GE_MESSAGE_H
