const puppeteer = require("puppeteer");

const main = async () => {
  const browser = await puppeteer.launch({
    headless: "new",
  });
  const page = await browser.newPage();

  await page.goto("https://loy124.github.io/vue-movie/");
  const movies = await page.evaluate(() => {
    const movieNamesEls = document.querySelectorAll(".movie-title");
    const titles = Array.from(movieNamesEls).map((el) => el.textContent);

    const movieScoreEls = document.querySelectorAll(".img-fluid");
    const scores = Array.from(movieScoreEls).map((el) => el.src);

    // logic
    const movies = titles.map((title, idx) => {
      return {
        title: title,
        src: scores[idx],
      };
    });
    return movies;
  });
  console.log(movies);
  await browser.close();
};

main();