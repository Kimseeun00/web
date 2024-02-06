class Calculator{
    constructor(){
        this.result = 0;
    }
    
    add(number){
        this.result += number;
        return this;
    }
    subtract(number){
        this.result -= number;
        return this;
    }
    multiply(number){
        this.result *= number;
        return this;
    }
    getResult(){
        return this.result;
    }
}

const calculator = new Calculator();

const result = calculator.add(5).subtract(3).multiply(10).getResult();