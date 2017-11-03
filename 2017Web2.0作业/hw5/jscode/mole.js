(function() {
    'use strict';
    const GAME_STATUS = {'PLAYING': 'Playing', 'GAMEOVER': 'Game Over'};
    const gameStatus = document.getElementById('game-status');
    const timeCounter = document.getElementById('time-count');
    const scoreCounter = document.getElementById('score-count');
    const moleColorClassName = {'ORIGINAL': 'mole-original', 'TOCLICK': 'mole-to-click'}
    var isGameStatus = false,
        timeCounterID,
        molesDiv = document.createElement('div'),
        i,
        j;
    
    // if a mole be clicked
    function moleBeClicked() {  // if game is on and player clicked correctly
        if (isGameStatus) {
            if (this.className == moleColorClassName['TOCLICK']) {
                ++scoreCounter.innerText;
                this.className = moleColorClassName['ORIGINAL'];    // restore itself
                makeRandomMole();                                   // get a mole randomly
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
            var mole = document.createElement('button');
            mole.className = moleColorClassName['ORIGINAL'];
            mole.style.marginLeft = mole.style.marginRight = "0.3%";
            mole.onclick = moleBeClicked;
            mole.style.outline = "none";
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
    // buttons restore original color
    function buttonTurnToOriginalColor() {
        var toClickButtons = document.getElementsByClassName(moleColorClassName['TOCLICK']);
        if (toClickButtons.length > 0) {
            toClickButtons[0].className = moleColorClassName['ORIGINAL'];
        }
    }

    // randomly generate a mole for clicking
    const moles = document.getElementsByClassName(moleColorClassName['ORIGINAL']);
    function makeRandomMole() {
        moles[Math.floor(Math.random() * 60)].className = moleColorClassName['TOCLICK'];
    }

    // game over to do
    function gameOver() {
        clearInterval(timeCounterID);   // stop time count down
        displayScoreByAlert();          // alert to display player's score
        buttonTurnToOriginalColor();    // turn into orginal color
        gameStatus.innerText = GAME_STATUS['GAMEOVER']; // display game status
        isGameStatus = false;           // set game status flag
    }
    // game on to do
    function gameStart() {
        timeCounterID = setInterval(timeCountDown, 1000);    // begin to count down by 1s
        scoreCounter.innerText = 0;     // init the score
        timeCounter.innerText = 30;     // init the time
        makeRandomMole();               // randomly generate a mole to click
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