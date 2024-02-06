// 토글 버튼
const toggleButton = document.querySelector(".toggle-button");
//body
const body = document.querySelector("body");

//header의 ul
const header = document.querySelector(".header-nav-list-wrapper")
// bookmarkText
const bookmarkText = document.querySelectorAll(".bookmark-text");
//searchInput
const searchInput = document.querySelector(".search-input");

toggleButton.addEventListener("click", function(){
    toggleButton.classList.toggle("toggle-button-darkmode");
    body.classList.toggle("body-background-darkmode");

    if(toggleButton.classList.contains("toggle-button-darkmode")){
        toggleButton.textContent = "일반 모드";
    }else{
        toggleButton.textContent = "다크 모드";
    }
    header.classList.toggle("text-darkmode");

    for(let i = 0; i < bookmarkText.length; i++){
        bookmarkText[i].classList.toggle("text-darkmode");
    }

}); 