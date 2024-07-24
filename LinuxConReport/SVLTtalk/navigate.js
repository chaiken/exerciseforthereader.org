// Slide navigation. Requires slides called slideXX.html .

/* http://www.quirksmode.org/js/keys.html
Logitech presenter: 
Pushing buttons generates onkeydown/onkeyup events, but *not* onkeypress.
left arrow = ", keynum 34
right arrow = !, keynum 33
right arrow in box is t, keynum 27
box with underline is 3/4, keynum 190 or 46
*/

// http://www.w3schools.com/jsref/event_button.asp
/* function whichButton(event)
{
    switch(event.button)
    {
    case 0:
	alert("Button 0");
	break;
    case 1:
	alert("Button 1");
	break;
    case 2:
	alert("Button 2");
	break;
    case 3: 
	alert("Button 3");
	break;
    case 4:
	alert("Button 4");
	break;
    case 5:
	alert("Button 5");
	break;
    case 6:
	alert("Button 6");
	break;
    case 7:
	alert("Lets see you do that again.");
	break;
    default:
	alert("You clicked a diff button.");
    }
} */

function whichButton(event)
{
    switch(event.button)
    {
    case 0:
	//alert("Button 0");  // left button
	nextSlide();
	break;
    case 1:
	//alert("Button 1");  // middle button
	prevSlide();
	break;
    default:
//	alert("You clicked a diff button.");
	upSlide();
    }
}

function clickAlert(e) {
    var clickEvent;

if(window.event) // IE
    {
	alert("Button event");
    }
    else if(e.which) // Netscape/Firefox/Opera
    {
	alert("Button event");
    }
    
}

// http://www.w3schools.com/jsref/event_onkeypress.asp
function keyAlert(e) {
    var keynum;
    var keychar;
    var usrMsg;

if(window.event) // IE
{
    keynum = e.keyCode;
}
else if(e.which) // Netscape/Firefox/Opera
{
    keynum = e.which;
}
    keychar = String.fromCharCode(keynum);
    //usrMsg = "Keychar is " + keychar;
//    usrMsg = "Keynum is " + keynum;
//    alert(usrMsg);

    if ((keychar == "p") || (keynum == 33)) {
	prevSlide();
    }
    if ((keychar == "n") || (keynum == 34)) {
	nextSlide();
    }
    if ((keychar == "u") || (keynum == 27) || (keynum == 190) || (keynum == 46))
 {
// any key on Logitech presenter but left or right arrows; may need to press several times
	upSlide();
    }
}

function prevSlide() {
  var url = new String(window.location);
  var number = url.substr(url.length - 7, 2);
  number--;

  if (document.getElementById && document.getElementById('last_slide'))
    { window.location="slide17.html"; }
  else if (number.toString().length == 1) {
    number = "0" + number.toString();
    window.location="slide" + number + ".html";
  }
  else if (number.toString().length == 2) {
    number = number.toString();
    window.location="slide" + number + ".html";
  }
  if (number == -1) window.location="summary.html";

  // Let's not run off the end of the slides
  // if (number == 0) { return 0; } {
  //     number--;
  // 
  // window.location="slide" + number + ".html";
}

function nextSlide() {
  var url = new String(window.location);
  var number = url.substr(url.length - 7, 2);

//    onkeypress="alert('Key pressed')";
  number++;

   // onkeydown="alert(Detected nextSlide)";

  // We use a <span id='last_slide' /> to denote the last slide.
  if (document.getElementById && document.getElementById('last_slide'))
    { window.location="slide00.html"; }

  else if (number.toString().length == 1) {
    number = "0" + number.toString();
    window.location="slide" + number + ".html";
  }
  else if (number.toString().length == 2) {
    number = number.toString();
    window.location="slide" + number + ".html";
  }
}

function upSlide() {
    window.location="overview.html";
}
