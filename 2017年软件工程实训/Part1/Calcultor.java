/*
    A simple calcultor to compute two 64-bit numbers. 
    Author : ugnamsung
    Date : 2017-03-18
*/


import javax.swing.*;
import javax.swing.BorderFactory;
import javax.swing.border.Border;
import java.awt.*;
import java.awt.Insets;
import java.awt.Dimension;
import java.awt.event.*;
import java.lang.Long.*;
import java.lang.Double.*;
import java.lang.Integer.*;
import java.util.regex.*;
import java.lang.*;
import java.lang.Math;

public class Calcultor {
    
    private static class Symbol {   // 操作数符号
        private static String EQUAL = "=";
        private static String PLUS = "+";
        private static String MINUS = "-";
        private static String MULTIPLY = "*";
        private static String DIVIDE = "/";
    }
    
    private final static String EMPTY_STRING = ""; // 空字符串
    private final static String FRAME_NAME = "Calcultor"; // 计算器标题
    private final static String OK_STRING = "OK"; // 空字符串

    private static void SimpleCalcultor() {

        JFrame frame = new JFrame(FRAME_NAME);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 200);

        // 布置局面
        Container cp = frame.getContentPane();
        cp.setLayout(new GridLayout(2, 5, 4, 4));

        //---------------网格第一行----------------------
        // 两个文本框输入操作数
        JTextField firstOperand = new JTextField(EMPTY_STRING);
        JTextField secondOperand = new JTextField(EMPTY_STRING);
        // 标签:操作符，等于号，得数　默认居中　有黑色边框
        JLabel operator = new JLabel(EMPTY_STRING, SwingConstants.CENTER);
        Border operatorBorder = BorderFactory.createLineBorder(Color.BLACK, 2);
        operator.setBorder(operatorBorder);
        JLabel equal = new JLabel(Symbol.EQUAL, SwingConstants.CENTER);
        Border equalBorder = BorderFactory.createLineBorder(Color.BLACK, 2);
        equal.setBorder(equalBorder);
        JLabel result = new JLabel(EMPTY_STRING, SwingConstants.CENTER);
        Border resultBorder = BorderFactory.createLineBorder(Color.BLACK, 2);
        result.setBorder(resultBorder);

        cp.add(firstOperand);
        cp.add(operator);
        cp.add(secondOperand);
        cp.add(equal);
        cp.add(result);

        //---------------网格第二行----------------------
        JButton plusButton = new JButton(Symbol.PLUS);
        JButton minusButton = new JButton(Symbol.MINUS);
        JButton multiplyButton = new JButton(Symbol.MULTIPLY);
        JButton divideButton = new JButton(Symbol.DIVIDE);
        JButton okButton = new JButton(OK_STRING);
        
        // 添加okButton的动作监听
        okButton.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent ae) {
                double firstNum = 0;
                double secondNum = 0;
                double resultNum = 0;
                boolean isError = false;    // 判断是否出现错误
                // 判断是否可以获取数字（可能有非法字符、空字符或溢出的数字）
                try {
                    firstNum = getDoubleFromString(firstOperand.getText());
                    secondNum = getDoubleFromString(secondOperand.getText());
                } catch (NumberFormatException e) {
                    isError = true;
                }
                // 是否溢出
                if (isOverFlow(firstNum) || isOverFlow(secondNum)) {
                    isError = true;
                }
                if (!isError) {
                    switch(operator.getText()) {
                        case "+": resultNum = firstNum + secondNum;
                            break;
                        case "-": resultNum = firstNum - secondNum;
                            break;
                        case "*": resultNum = firstNum * secondNum;
                            break;
                        case "/":
                            try {
                                resultNum = firstNum / secondNum;
                            } catch (ArithmeticException e) {   // 除以０
                                isError = true;
                            }
                            break;
                        default: isError = true;    // 操作符非法
                    }
                    if (isOverFlow(resultNum)) {   // 是否溢出
                        isError = true;
                    }
                }

                if (isError) {
                    result.setText(EMPTY_STRING);
                } else {
                    result.setText(getStringFromDouble(resultNum));
                }
            }
        });
        // 添加操作符Button的动作监听
        ActionListener operatorAction = new ActionListener() {
            public void actionPerformed(ActionEvent ae) {
                JButton choosedOperator = (JButton) ae.getSource();
                if (choosedOperator == plusButton){
                    operator.setText(Symbol.PLUS);
                }
                else if (choosedOperator == minusButton){
                    operator.setText(Symbol.MINUS);
                }
                else if (choosedOperator == multiplyButton){
                    operator.setText(Symbol.MULTIPLY);
                }
                else {
                    operator.setText(Symbol.DIVIDE);
                }
            }
        };

        plusButton.addActionListener(operatorAction);
        minusButton.addActionListener(operatorAction);
        multiplyButton.addActionListener(operatorAction);
        divideButton.addActionListener(operatorAction);

        cp.add(plusButton);
        cp.add(minusButton);
        cp.add(multiplyButton);
        cp.add(divideButton);
        cp.add(okButton);
        //--------------网格布局完成--------------------

        frame.setVisible(true);
    }
    // 字符串-->数字
    private static double getDoubleFromString(String textString) {
        return Double.parseDouble(textString);
    }
    // 判断是否溢出
    private static boolean isOverFlow(double num) {
        return num > Long.MAX_VALUE || num < Long.MIN_VALUE;
    }
    private static String getStringFromDouble(double num) {
        return String.valueOf(Long.toString(Math.round(num)));
    }
    public static void main(String[] args) {
        Runnable tr = new Runnable() {
            public void run() {
                SimpleCalcultor();
            }
        };
        javax.swing.SwingUtilities.invokeLater(tr);
    }


}