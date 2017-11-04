(function() {
    'use strict';
    const GAME_STATUS = {'PLAYING': 'Playing', 'GAMEOVER': 'Game Over'};
    const gameStatus = document.getElementById('game-status');
    const timeCounter = document.getElementById('time-count');
    const scoreCounter = document.getElementById('score-count');
    var isGameStatus = false,
        timeCounterID,
        molesDiv = document.createElement('div'),
        indexToClick,       // the index of the button to click
        i,
        j;
    
    // if a mole be clicked
    function moleBeClicked() {  // if game is on and player clicked correctly
        if (isGameStatus) {
            this.checked = false;       // restore itself
            if (this.index == indexToClick) {
                ++scoreCounter.innerText;
                makeRandomMole();       // get a mole randomly
            } else {
                --scoreCounter.innerText;
            }
        }
    }
    
    // dynamically create mole buttons
    for (i = 0; i < 6; i++) {
        var moleRowDiv = document.createElement('div');
        moleRowDiv.style.textAlign = "center";
        for (j = 0; j < 10; j++) {
            var mole = document.createElement('input');
            mole.type = "radio";
            mole.className = "mole-original";
            mole.onclick = moleBeClicked;
            mole.disabled = true;
            mole.index = i * 10 + j;
            moleRowDiv.appendChild(mole);
        }
        molesDiv.appendChild(moleRowDiv);
    }
    document.getElementById('moles-position').insertBefore(molesDiv,
        document.getElementById('moles-position').getElementsByTagName('hr')[1]);

    // alert to display score when game ends
    function displayScoreByAlert() {
        alert(GAME_STATUS['GAMEOVER'] + '.\nYour socre is: ' + scoreCounter.innerText);
    }

    // randomly generate a mole for clicking
    const moles = document.getElementsByTagName('input');
    function makeRandomMole() {
        moles[(indexToClick = Math.floor(Math.random() * 60))].checked = true;
    }

    // set buttons diabled or abled
    function makeDisabledTrueOrFalse(disabledValue) {
        for (var k = 0; k < moles.length; k++) {
            moles[k].disabled = disabledValue;
        }
    }

    // buttons restore original color
    function buttonTurnToOriginal() {
        moles[indexToClick].checked = false;
        makeDisabledTrueOrFalse(true);
    }

    // game over to do
    function gameOver() {
        clearInterval(timeCounterID);   // stop time count down
        displayScoreByAlert();          // alert to display player's score
        buttonTurnToOriginal();    // turn into orginal color
        gameStatus.innerText = GAME_STATUS['GAMEOVER']; // display game status
        isGameStatus = false;           // set game status flag
    }
    // game on to do
    function gameStart() {
        timeCounterID = setInterval(timeCountDown, 1000);    // begin to count down by 1s
        scoreCounter.innerText = 0;     // init the score
        timeCounter.innerText = 30;     // init the time
        makeRandomMole();               // randomly generate a mole to click
        makeDisabledTrueOrFalse(false); // make disbled of  all buttons false
        gameStatus.innerText = GAME_STATUS['PLAYING'];  // display game status
        isGameStatus = true;            // set game status flag
    }

    // the timer to count down in 30s and the game will over at 0s
    function timeCountDown() {
        --timeCounter.innerText;
        if (timeCounter.innerText == 0) {
            gameOver();
        }
    }
    
    // the button for game start or stop
    document.getElementById('start-stop').onclick = function() {
        if (isGameStatus) {         // if game is on, stop the game
            gameOver();
        } else {                    // if game is over, restart the game
            gameStart();
        }
    };
}());