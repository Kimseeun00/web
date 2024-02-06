// class 는 첫자를 대문자로 시작

class Student{
    // 생성할 때 호출되는 초기화 메서드
    constructor(name,age,me){
       this.name = name;
       this.age = age;
       this.me = me;
    }

   introduce(){
        console.log(`이름 : ${this.name}`)
        console.log(`나이 : ${this.age}`)
        console.log(`자기소개 : ${this.me}`)
    }
    
}

const one = new Human("김세은",31,"반갑습니다");
one.introduce();