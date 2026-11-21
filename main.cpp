#include <iostream>

const std::string ONES[] = {"",     "one", "two",   "three", "four",
                            "five", "six", "seven", "eight", "nine"};
const std::string TEENS[] = {"ten",      "eleven",  "twelve",  "thirteen",
                             "fourteen", "fifteen", "sixteen", "seventeen",
                             "eighteen", "nineteen"};

const std::string TENS[] = {"",      "",      "twenty",  "thirty", "forty",
                            "fifty", "sixty", "seventy", "eighty", "ninety"};
const std::string MULTIPLIER[] = {"",        "thousand", "million",
                                  "billion", "trillion", "quadrillion"};

static void appendWord(std::string &result, const std::string_view word) {
  if (word.empty()) {
    return;
  }

  if (!result.empty()) {
    result.append(" ");
  }

  result.append(word);
}

static std::string threeDigitsToWords(unsigned long number) {
  if (number == 0) {
    return "";
  }

  if (number < 0 || number > 999) {
    return "Invalid";
  }

  std::string word;

  const unsigned long hundredths = number / 100;
  if (hundredths > 0) {
    word = ONES[hundredths] + " hundred";
  }

  number = number % 100; // tens

  const unsigned long tenths = number / 10;
  const unsigned long ones = number % 10;

  if (tenths > 1) {
    // 20 - 90
    appendWord(word, TENS[tenths]);
    if (ones > 0) {
      appendWord(word, ONES[ones]);
    }
  } else if (tenths == 1) {
    // 10 - 19
    appendWord(word, TEENS[ones]);
  } else {
    appendWord(word, ONES[ones]); // 1 - 9
  }

  return word;
}

static std::string convertNumberToWords(unsigned long number) {
  if (number == 0) {
    return "zero";
  }

  std::string response;
  std::size_t group = 0;
  while (number > 0) {
    unsigned long value = number % 1000;

    std::string subWord = threeDigitsToWords(value);

    if (!subWord.empty()) {
      if (response.empty()) {

        response = group == 0 ? subWord : subWord + " " + MULTIPLIER[group];
      } else {
        response = subWord + " " + MULTIPLIER[group] + " " + response;
      }
    }

    number = number / 1000;

    ++group;
  }

  return response;
}

int main() {
  int numberToConvert;

  std::cout << "Number to convert: ";
  std::cin >> numberToConvert;

  const std::string word = convertNumberToWords(numberToConvert);

  std::cout << "Word: " << word << std::endl;

  return 0;
}
