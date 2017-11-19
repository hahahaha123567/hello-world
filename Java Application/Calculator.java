// recursive descent

import java.util.ArrayList;
import java.util.Scanner;

interface Token { }

class Operator implements Token {
    private char op;
    Operator (String arg) { this.op = arg.charAt(0); }
    @Override
    public String toString() { return "" + op; }
}

class Operand implements Token {
    private int op;
    Operand (String arg) { this.op = Integer.parseInt(arg); }
    @Override
    public String toString() { return "" + op; }
}

class Lexer {
    private char[] operators = {'+', '-', '*', '/', '%', '(', ')'};

    private ArrayList<Token> tokens = new ArrayList<>();
    private int index;
    private char nextChar;

    Lexer (String input) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < input.length(); ++i) {
            char temp = input.charAt(i);
            if (isOperator(temp)) {
                if (sb.length() != 0) {
                    tokens.add(new Operand(sb.toString()));
                    sb.setLength(0);
                }
                tokens.add(new Operator("" + temp));
            } else { // else if (Character.isDigit(temp))
                sb.append(temp);
            }
        }
        if (sb.length() != 0) {
            tokens.add(new Operand(sb.toString()));
            sb.setLength(0);
        }
        nextChar = tokens.get(0).toString().charAt(0);
    }

    Token getToken () {
        index++;
        if (index < tokens.size()) {
            nextChar = tokens.get(index).toString().charAt(0);
        }
        return tokens.get(index-1);
    }

    boolean addOrSub () {
        return index < tokens.size() && (nextChar == operators[0] || nextChar == operators[1]);
    }

    boolean mulOrDiv () {
        return index < tokens.size() && (nextChar == operators[2] || nextChar == operators[3] || nextChar == operators[4]);
    }

    boolean leftBra () { return index < tokens.size() &&  nextChar == operators[5]; }

    private boolean isOperator (char op) {
        boolean ret = false;
        for (char operator : operators) {
            if (op == operator) { ret = true; }
        }
        return ret;
    }
}

class Parser {
    private Lexer lexer;

    Parser (Lexer lexer) { this.lexer = lexer; }

    int getValue () { return expression(); }

    // expression -> term +|- term
    private int expression () {
        int ret = term();
        while (lexer.addOrSub()) {
            Token token = lexer.getToken();
            int op2 = term();
            switch (token.toString()) {
                case "+": ret += op2; break;
                case "-": ret -= op2;
            }
        }
        return ret;
    }

    // term -> value * | / | % value
    private int term () {
        int ret = value();
        while (lexer.mulOrDiv()) {
            Token token = lexer.getToken();
            int op2 = value();
            switch (token.toString()) {
                case "*": ret *= op2; break;
                case "/": ret /= op2; break;
                case "%": ret %= op2;
            }
        }
        return ret;
    }

    // value -> NUMBER | (expression) | +value | -value
    private int value () {
        int ret;
        if (lexer.leftBra()) {
            lexer.getToken(); // pop the left bracket
            ret = expression();
            lexer.getToken(); // pop the right bracket
        } else if (lexer.addOrSub()) {
            Token sign = lexer.getToken();
            switch (sign.toString()) {
                case "+": ret = value(); break;
                case "-": ret = 0 - value(); break;
                default: ret = 0; // won't reach
            }
        } else {
            ret = Integer.parseInt(lexer.getToken().toString());
        }
        return ret;
    }
}

public class Calculator {
    public static void main (String[] args) {
        Scanner in = new Scanner(System.in);
        String input = in.nextLine();
        Lexer lexer = new Lexer(input);
        Parser parser = new Parser(lexer);
        System.out.println(parser.getValue());
    }
}
