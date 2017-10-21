'use strict';

// 常量的定义
const MINUS = "-";
const PLUS = '+';
const DIVIDE = '/';
const MULTIPLY = '*';
const POINT = '.';
const LEFT_BRACKET = '(';
const RIGHT_BRACKET = ')';
const LEFT_BRACKET_SIGN = 1;
const RIGHT_BRACKET_SIGN = 2;
const BRACKET = {'(': LEFT_BRACKET_SIGN, ')': RIGHT_BRACKET_SIGN};
const LOW_PRORITY = 3;
const HIGH_PRORITY = 4;
const PRORITY = {'/': HIGH_PRORITY, '*': HIGH_PRORITY, '+': LOW_PRORITY, '-': LOW_PRORITY};
const INPUT_ITEM_BUTTON_IDS = ["seven", "eight", "nine", 
                                "four", "five", "six", 
                                "one", "two", "three", "zero"];
const ARITH_BUTTON_IDS = ["divide", "multiply", "minus", "plus"];
const BRACKET_IDS = ["left-bracket", "right-bracket"];
const inputBox = document.getElementById('input-box');      // 输入框
inputBox.innerText = "\n0";
const scrollMoveStep = 20;      // 滚动条移动距离-
// const testOutput = document.getElementById('test-output');   // for debug
var inputBracketsNum = 0;       // 左右括号数量
var isDisplayResult = false;    // 是否正在显示上次计算的运行结果（2行显示）
var i;

// 判断符号
var isMinus = function(exp_char) {          // 判断是否负号
    return exp_char === MINUS;
}
var isArithSymbol = function(exp_char) {    // 判断是否四则运算符
    return PRORITY[exp_char];
}
var isBracket = function(exp_char) {        // 判断是否为括号及括号类型
    return BRACKET[exp_char];
}
var prorityOfSymbol = function(exp_char) {  // 判断符号的优先级
    return PRORITY[exp_char];
}
var isPoint = function(exp_char) {          // 判断是否为小数点
    return exp_char === POINT;
}
var isDigit = function(exp_char) {          // 判断是否为数字
    // 是否由数字和小数点组成
    if ((exp_char <= '9' && exp_char >= '0') || isPoint(exp_char)) {
        return true;
    } else {
        return false;
    }
}
var isLeftBracket = function(exp_char) {    // 判断是否为左括号
    return exp_char === LEFT_BRACKET;
}
var isRightBracket = function(exp_char) {   // 判断是否为右括号
    return exp_char === RIGHT_BRACKET;
}
var isHighPrority = function(exp_char) {    // 判断是否为高级运算符乘除
    return prorityOfSymbol(exp_char) === HIGH_PRORITY;
}
var isLowPrority = function(exp_char) {     // 判断是否为低级运算符加减
    return prorityOfSymbol(exp_char) === LOW_PRORITY;
}
var isTypeNumber = function(exp_char) {     // 判断变量是否为数字
    return typeof(exp_char) === "number";
}
// -----------------------------------------------------

var inputNumbers = function() {            // 输入数字
    if (isDisplayResult) {
        cleanUp();
    }
    if (inputBox.innerText.length >= 2 && inputBox.innerText.slice(-1) === '0' && 
    !isDigit(inputBox.innerText.slice(-2, -1))) {
        inputBox.innerText = inputBox.innerText.slice(0, -1) + this.innerText;
    }
    else {
        inputBox.innerText += this.innerText;        
    }
    inputBox.scrollTo(inputBox.scrollLeft + scrollMoveStep * 2, 0);
}
// 设置数字的按钮点击事件
for (i = 0; i < INPUT_ITEM_BUTTON_IDS.length; i++) {
    document.getElementById(INPUT_ITEM_BUTTON_IDS[i]).onclick = inputNumbers;
}

// 设置左括号的按钮点击事件
document.getElementById("left-bracket").onclick = function() {
    if (isDisplayResult) {
        cleanUp();
    }
    if (inputBox.innerText.length >= 2 && inputBox.innerText.slice(-1) === '0' && 
    !isDigit(inputBox.innerText.slice(-2, -1))) {
        inputBox.innerText = inputBox.innerText.slice(0, -1) + this.innerText;
    }
    else {
        inputBox.innerText += this.innerText;        
    }
    ++inputBracketsNum;
    inputBox.scrollTo(inputBox.scrollLeft + scrollMoveStep * 2, 0);
}
// 设置右括号的按钮点击事件
document.getElementById("right-bracket").onclick = function() {
    if (isDisplayResult) {
        cleanUp();
    }
    if (inputBracketsNum > 0) {
        var expEndChar = inputBox.innerText.slice(-1);
        if (isArithSymbol(expEndChar)) {  // the last char of expression is arith
            inputBox.innerText = inputBox.innerText.slice(0, -1) + this.innerText;
        }
        else {
            inputBox.innerText += this.innerText;
        }
        --inputBracketsNum;
    }
    inputBox.scrollTo(inputBox.scrollLeft + scrollMoveStep * 2, 0);
}

// 设置小数点的按钮点击操作
// 输入小数点,检查输入框表达式从最后一个字符到最后出现的一个“四则运算/括号”(非数字)字符之间没有小数点
document.getElementById("point").onclick = function() {
    if (isDisplayResult) {
        cleanUp();
    }
    var i;
    var existPointFlag = false;
    for (i = inputBox.innerText.length - 1; i >= 0; i--) {
        var exp_char = inputBox.innerText[i];
        if (!isDigit(exp_char)) {
            break;
        } else if (isPoint(exp_char)) {
            existPointFlag = true;
            break;
        }
    }
    if (!existPointFlag) {
        if (i && !isDigit(inputBox.innerText.slice(-1))) {  // 前一个字符不是数字或小数点
            inputBox.innerText += '0' + this.innerText;     // 补上一个'0' '.' => '0.'
        } else {
            inputBox.innerText += this.innerText;
        }
    }
    inputBox.scrollTo(inputBox.scrollLeft + scrollMoveStep * 2, 0);
}

// 输入四则运算
// 如果输入框表达式最后是以四则运算符结尾，则最后的四则运算符被新输入运算符替换
var inputArithSymbol = function() {
    if (isDisplayResult) {
        cleanUp();
    }
    var expEndChar = inputBox.innerText.slice(-1);
    if (isArithSymbol(expEndChar)) {  // the last char of expression is arith
        inputBox.innerText = inputBox.innerText.slice(0, -1) + this.innerText;
    }
    else {
        inputBox.innerText += this.innerText;
    }
    inputBox.scrollTo(inputBox.scrollLeft + scrollMoveStep * 2, 0);
}
// 设置四则运算的按钮点击事件
for (i = 0; i < ARITH_BUTTON_IDS.length; i++) {
    document.getElementById(ARITH_BUTTON_IDS[i]).onclick = inputArithSymbol;
}

// 设置删除按钮点击事件
document.getElementById("delete").onclick = function() {
    if (isDisplayResult) {
        cleanUp();
    } else {
        var text = inputBox.innerText.slice(1); // 去掉\n
        if (text.length > 1) {
            inputBox.innerText = "\n" + text.slice(0, -1);  // 删除最后一个元素
        }
        else if (text != "0") {
            inputBox.innerText = "\n0";    
        }
    }
    inputBox.scrollTo(inputBox.scrollLeft + scrollMoveStep * 2, 0);
}
// 清除显示，默认为0
var cleanUp = function() {
    inputBox.innerText = "\n0";
    isDisplayResult = false;
}
// 设置CE清除按钮点击事件
document.getElementById("clean-up").onclick = cleanUp;

// -------------------------------------------------------

// 判断表达式是否有效
var isValid = function(expression) {
    if (expression.length === 0) {   // 空字符串
        return false;
    }
    var isSymBraket = 0;            // 数括号
    var i;
    for (i = 0; i <= expression.length; i++) {
        if (i === expression.length) {  // 达到表达式结尾
            // 有四则运算符或左括号
            if (isArithSymbol(expression[i-1]) || isLeftBracket(expression[i-1])) {
                return false;
            }
            break;
        }
        else if (isArithSymbol(expression[i])) {
            if (i && isArithSymbol(expression[i-1])) {  // 两个运算符连在一起
                return false;
            }
             // 非减号的运算符是首字符 或 在左括号后面
            if (prorityOfSymbol(expression[i]) != LOW_PRORITY && (
                i == 0 || isLeftBracket(expression[i-1]))) {
                return false;
            }
        }
        else if (isLeftBracket(expression[i])) {    // 左括号
            if (i && isDigit(expression[i-1])) {    // 前面是数字
                return false;
            }
            ++isSymBraket;                          // 有左括号就加1
        }
        else if (isRightBracket(expression[i])) {   // 右括号
            // 前面没有左括号 或 前面是四则运算符或左括号'..+)' '()'
            if (isSymBraket <= 0 || isArithSymbol(expression[i-1]) || isLeftBracket(expression[i-1])) {
                return false;
            }
            --isSymBraket;
        }
        else if (isDigit(expression[i])) {
            if (i && isRightBracket(expression[i-1])) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return isSymBraket === 0;
}

// 判断栈是否为空
var isEmptyStack = function(stack) {
    return stack.length === 0;
}
// 获取栈顶元素
var getStackTopData = function(stack) {
    if (stack.length) {
        return stack[stack.length - 1];
    }
}

// 中缀表达式字符串转化成后缀表达式栈
var inFixToSuffix = function(inputExpression) {
    var opExpStack = [];                    // 用来放操作符的表达式栈
    var suffixStack = [];                   // 后缀表达式栈
    var isMinus = false;                    // 判断是否为负数
    var i = 0;
    while (i < inputExpression.length) {
        if (isDigit(inputExpression[i])) {  // 数字
            var start = i;
            while(i + 1 < inputExpression.length && isDigit(inputExpression[++i]));
            var end = i - 1;
            if (isDigit(inputExpression[i])) {
                end = i;
            } else {
                --i;
            }
            if (isMinus) {
                isMinus = false;
                suffixStack.push(-parseFloat(inputExpression.slice(start, end + 1)));
            } else {
                suffixStack.push(parseFloat(inputExpression.slice(start, end + 1)));                
            }
        }
        else if (isLeftBracket(inputExpression[i])) {   // 左括号
            opExpStack.push(inputExpression[i]);
        }
        else if (isHighPrority(inputExpression[i])) {   // 乘除（优先级高）
            // 把栈里的高级运算符 * /，都输出
            while(!isEmptyStack(opExpStack)) {
                if (!isHighPrority(getStackTopData(opExpStack))) {
                    break;
                } else {
                    suffixStack.push(opExpStack.pop());
                }
            }
            // 再把这个操作符放进栈里面
            opExpStack.push(inputExpression[i]);
        }
        else if (isRightBracket(inputExpression[i])) {  // 右括号
            // 依次把栈中的的运算符加入后缀表达式中
            // 直到出现'('，从栈中删除'(' 
            var popData = opExpStack.pop();
            while (popData != '(') {
                suffixStack.push(popData);
                popData = opExpStack.pop();
            }
        }
        else if (isLowPrority(inputExpression[i])) {    // 优先级低的运算符 加减
            // 先判断是不是代表正负号，而不是加减号，eg.是一个负数 '-x' '(-x' ; 是一个减号： 'x-x' ‘x-(''
            if ((i == 0 || isLeftBracket(inputExpression[i-1]) && isDigit(inputExpression[i+1]))) {
                if (inputExpression[i] === MINUS) {
                    isMinus = true;
                }
            }
            else {
                // 将从栈顶到第一个优先级等于它的运算符（或 '(',但优先满足前一个条件）
                // 之间的运算符加入后缀表达式中，该运算符再入栈
                while (!isEmptyStack(opExpStack)) {
                    var popData = opExpStack.pop();
                    if (popData === '(') {
                        opExpStack.push(popData);
                        break;
                    }
                    else {
                        suffixStack.push(popData);
                    }
                }
                opExpStack.push(inputExpression[i]);
            }
        }
        ++i;
    }
    // 把操作符栈里剩下的操作符全部放进后缀表达式栈
    while (!isEmptyStack(opExpStack)) {
        suffixStack.push(opExpStack.pop());
    }
    return suffixStack;
}
// 获得小数长度
var getDecimalsLength = function(x) {
    var x_split = x.toString().split('.');
    return x_split.length > 1 ? x_split[1].length : 0;
}
// 把小数转化成整数
var decimalsToInteger = function(x) {
    return Number(x.toString().replace('.', ''));
}
// 加减乘除四则运算 减少浮点数精度的干扰
var divide = function(x, y) {
    var xDecLen = getDecimalsLength(x);
    var yDecLen = getDecimalsLength(y);
    var result = (decimalsToInteger(x) / decimalsToInteger(y)) * Math.pow(10, yDecLen - xDecLen);
    return result;
}

var plus = function(x, y) {
    var xDecLen = getDecimalsLength(x);
    var yDecLen = getDecimalsLength(y);
    var lenDiffPowTen = Math.pow(10, Math.abs(xDecLen - yDecLen));
    if (xDecLen > yDecLen) {
        x = decimalsToInteger(x);
        y = decimalsToInteger(y) * lenDiffPowTen;
    }
    else {
        x = decimalsToInteger(x) * lenDiffPowTen;
        y = decimalsToInteger(y);
    }
    return (x + y) / Math.pow(10, Math.max(xDecLen, yDecLen));
}

var minus = function (x, y) {
    var xDecLen = getDecimalsLength(x);
    var yDecLen = getDecimalsLength(y);
    var maxLen = Math.max(xDecLen, yDecLen);
    var maxLenPowTen = Math.pow(10, maxLen);
    return Number(((x * maxLenPowTen - y * maxLenPowTen) / maxLenPowTen).toFixed(maxLen));
}

var multiply = function(x, y) {
    var xDecLen = getDecimalsLength(x);
    var yDecLen = getDecimalsLength(y);
    return decimalsToInteger(x) * decimalsToInteger(y) / Math.pow(10, xDecLen + yDecLen);
}
// -------------------------------------------------------------------------
// 计算后缀表达式
var calculator = function(suffixStack) {
    var calStack = [];
    var result = 0;
    var i;
    for (i = 0; i < suffixStack.length; i++) {
        if (isTypeNumber(suffixStack[i])) { // 如果是数字
            var data = suffixStack[i];
            if (suffixStack.length == 1) {
                result = data;
            } else {
                calStack.push(data);
            }
        }
        else {
            var data1 = calStack.pop();
            var data2 = calStack.pop();
            switch (suffixStack[i]) {
                case PLUS:
                    result = plus(data2, data1);
                    break;
                case MINUS:
                    result = minus(data2, data1);
                    break;
                case DIVIDE:
                    if (data1 === 0) {
                        return 'Divide by zero';
                    }
                    result = divide(data2, data1);
                    break;
                case MULTIPLY:
                    result = multiply(data2, data1);
                    break;
                default:
                    return "Error!";
            }
            // testOutput.innerText += String.format('result = {0} type = {1}\n', result, typeof(result));
            calStack.push(result);
        }
    }
    
    return result;
}

// 计算表达式
var calculateInputExpression = function(inputExpression) {
    if (!isValid(inputExpression)) {
        alert('Sorry: Invalid expression!');
        return undefined;
    }
    var suffixStack = inFixToSuffix(inputExpression);
    // testOutput.innerText += suffixStack.join(',') + '\n';
    return calculator(suffixStack); 
}

// 字符串格式化
String.format = function(src){  
    if (arguments.length == 0) return null;  
    var args = Array.prototype.slice.call(arguments, 1);  
    return src.replace(/\{(\d+)\}/g, function(m, i){  
        return args[i];  
    });  
};

// 设置等于号按钮
document.getElementById("equal").onclick = function() {
    if (!isDisplayResult) {
        var expression = inputBox.innerText.slice(1);
        var result = calculateInputExpression(expression);
        if (isTypeNumber(result)) {
            // 和eval结果进行比较，确保不受精度影响，计算结果接近正常计算器
            var evalResult = eval(expression);
            if (getDecimalsLength(result) > getDecimalsLength(evalResult)) {
                result = evalResult;
            }
        }
        // else {
        //     testOutput.innerText += "wtf?\n";
        // }
        if (result != undefined) {
            inputBox.innerText = String.format('{0}\n{1}\n', expression, result);
            isDisplayResult = true;
        }
        inputBox.scrollTo(0, 0);
    }
}

// document.getElementById("test-button").onclick = function() {
//     testOutput.innerText = "";
// }

document.getElementById("left-move").onclick = function() {
    inputBox.scrollTo(inputBox.scrollLeft - scrollMoveStep, 0);
}

document.getElementById("right-move").onclick = function() {
    inputBox.scrollTo(inputBox.scrollLeft + scrollMoveStep, 0);
}