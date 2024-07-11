class myString
{
private:
    char *str;

    int length(const char *string)
    {
        int length = 0;
        while (string[length] != '\0')
            length++;

        return length;
    }
    int min(int a, int b)
    {
        return a < b ? a : b;
    }

public:
    myString(const char *string = "")
    {
        int len = length(string);
        str = new char[len + 1];
        for (short i = 0; i <= len; i++)
            str[i] = string[i];
    }

    ~myString()
    {
        delete[] str;
    }

    int length()
    {
        return length(str);
    }

    myString substr(int start, int len)
    {
        char *util = new char[len + 1];
        util[len] = '\0';
        for (size_t i = start; i < start + len; i++)
            util[i - start] = str[i];

        myString out(util);
        delete[] util;

        return out;
    }

    myString &toUpper()
    {
        for (int i = 0; i < length(); i++)
            if (str[i] <= 122 && str[i] >= 97)
                str[i] -= 32;
        return *this;
    }

    myString &toLower()
    {
        for (int i = 0; i < length(); i++)
            if (str[i] <= 90 && str[i] >= 65)
                str[i] += 32;
        return *this;
    }

    int find(const char *string)
    {
        int len = length(string);
        bool isSame;
        for (int currentIndex = 0; currentIndex < length(); currentIndex++)
        {
            isSame = true;
            if (str[currentIndex] == string[0])
            {
                int i;
                for (i = 1; i < len && i + currentIndex < length(); i++)
                    if (str[currentIndex + i] != string[i])
                    {
                        isSame = false;
                        break;
                    }
                if (isSame && i == len)
                    return currentIndex;
            }
        }
        return -1;
    }

    char *getText()
    {
        return str;
    }

    void replaceImmutable(const char *string, const char *newString)
    {
        int strPosition = find(string);
        if (strPosition != -1)
        {
            int len1 = length(newString);
            int len2 = length(string);
            myString backupStr = this->substr(strPosition + len2, length());
            for (int i = strPosition; i < strPosition + len1 && i < length(); i++)
                str[i] = newString[i - strPosition];
        }
    }

    void replace(const char *string, const char *newString)
    {
        int strPosition = find(string);
        if (strPosition != -1)
        {
            int len1 = length(newString);
            int len2 = length(string);
            int oldLen = length();
            myString backupStr = myString(this->getText());
            delete[] str;
            int newSize = oldLen + (len1 - len2) + 1;
            str = new char[newSize];
            int i;
            for (i = 0; i < strPosition; i++)
                str[i] = backupStr.at(i);
            for (; i < len1 + strPosition; i++)
                str[i] = newString[i - strPosition];
            for (; i < newSize; i++)
                str[i] = backupStr.at(i - ((newSize - 1) - oldLen));

            str[newSize - 1] = '\0';
        }
    }

    void append(const char *string, int index = -1)
    {
        myString copy = myString(this->getText());
        delete[] str;
        int strLen = length(string);
        int copyLen = copy.length();
        int len = copyLen + strLen + 1;
        str = new char[len];
        str[len - 1] = '\0';
        int i;
        if (index < 0)
        {
            for (i = 0; i < copyLen; i++)
                str[i] = copy[i];
            for (; i < len; i++)
                str[i] = string[i - copyLen];
        }
        else
        {
            int j;
            for (i = 0; i < index; i++)
            {
                str[i] = copy[i];
                j = i + 1;
            }
            for (; i < index + strLen; i++)
                str[i] = string[i - index];
            for (; i < len; i++, j++)

                str[i] = copy[j];
        }
    }

    bool isEmpty()
    {
        return length() == 0 ? 1 : 0;
    }

    char at(int index)
    {
        return str[index];
    }

    void at(int index, char c)
    {
        str[index] = c;
    }

    void clear()
    {
        delete[] str;
        str = new char;
        str[0] = '\0';
    }

    myString &operator=(const char *string)
    {
        if (str != string)
        {
            delete[] str;
            int len = length(string);
            str = new char[len + 1];
            for (int i = 0; i < len; i++)
                str[i] = string[i];
            str[len] = '\0';
        }
        return *this;
    }

    myString &operator+(const char *string)
    {
        int len1 = length(), len2 = length(string);
        char *copy = new char[len1 + 1];
        int index = 0;
        for (int i = 0; i <= len1; i++)
            copy[i] = str[i];

        delete[] str;

        str = new char[len1 + len2 + 1];
        int i;

        for (i = 0; i < len1; i++)

            str[i] = copy[i];

        for (i = 0; i <= len2; i++)

            str[i + len1] = string[i];

        delete[] copy;

        return *this;
    }

    char &operator[](unsigned short index)
    {
        return str[index];
    }

    bool operator==(const char *string)
    {
        if (length() == length(string))
        {
            for (int i = 0; i < length(); i++)
                if (str[i] != string[i])
                    return 0;
            return 1;
        }
        return 0;
    }

    bool operator>(myString &other)
    {
        int len = length();
        int oLen = length(other.getText());
        int minLen = min(len, oLen);

        for (auto i = 0; i < minLen; i++)
        {
            if (str[i] > other[i])
                return true;
            else if (str[i] < other[i])
                return false;
        }
        if (len > oLen)
            return true;
        return false;
    }

    bool operator<(myString &other)
    {
        return !(*this > other);
    }

    friend std::ostream &operator<<(std::ostream &os, const myString &other)
    {
        os << other.str;
        return os;
    }
};
