// 생성자에 인자가 없는 경우 상속

class Hero{
    constructor(){
        this.hp = 100;
    }
    run(){
        this.hp = this.hp - 10;
    }
}

class Superman extends Hero{
    fly(){
        console.log("fly");
        console.log(this.hp);
    }
}
const superman = new Superman();
superman.run();

// 생성자에 인자가 있는 경우 상속
class Animal{
    constructor(name){
        this.name = name;
    }

    speak(){
        console.log(`${this.name}이 울부짖습니다`);
    }
}

class Cat extends Animal{
    constructor(name){
        //Animal에 constructor 안에 name을 넣어줘야 한다.
        //이때 사용하는 키워드가 super 키워드
        super(name);
    }
}
