
String oneDecimal(double input){
  input = round(input * 10);
  input /= 10;   // Rounds to 1 decimal place
  String output = String(input);    // Stores in temporary string

  int index = output.lastIndexOf(".");  // Find decimal
  if (index != -1) {
    if (output.length() - index > 2) {
      output.remove(index + 2, output.length() - (index + 2));    // Trims zeroes
    }
  }
  
  return output;
}

void printCenter(int row, String message) {
  int pos = 10 - (message.length() + 1) / 2; // Finds start to center message (favours left)
  lcd.setCursor(pos, row);
  lcd.print(message);
}
void printRight(int row, String message) {
  int pos = 20 - message.length(); // Finds start to right justify the message (favours left)
  lcd.setCursor(pos, row);
  lcd.print(message);
}
void printLeft(int row, String message) {
  lcd.setCursor(0, row);
  lcd.print(message);
}
void printCursor() {
  lcd.setCursor(19 - maxFieldLength, field);
  lcd.print('>');
}
