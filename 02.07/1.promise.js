new Promise((resolve, reject) => {
    // 요청 성공시 resolve 호출
    // if (버그 발생시) {reject();}
})

const test = new Promise((resolve, reject) => {
    //위도 경도
    resolve(3);
}).then(li => {
    //console.log(li) <- 위도, 경도
    //API 호출을 해서 가져오면
})

//resolve 인 경우 then으로 가져오고
// reject 인 경우 catch로 가져온다.

// setTimeout <- promise화 시킬것

function promiseSetTimeout(time){
    return new Promise((resolve, reject) => {

        return setTimeout(() => {
            resolve(1)
        },time)
    })
}

// promise 형식은  .then .catch  붙이는게 가능
// 호출에 성공하고 나서 1초 후에 then으로 number 접근이 가능
promiseSetTimeout(1000).then(number => {
    console.log(number);
}).catch(error => {
    console.log(error);
})

// promise는 then을 여러 개 붙일 수 있다.
promiseSetTimeout(1000).then(li => {
    return li + 1
}).then(number => {
    console.log(number);
})