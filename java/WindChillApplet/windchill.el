;-*-lisp-interaction-*-
;x =  0.303439* Math.sqrt(windSpeed) - 0.0202886*windSpeed;
;		wcIndex = 91.9 - (91.4 - temperature)*(x+0.474266);


(defun windchill (windSpeed temperature)
  (- 91.9 (* (- 91.4 temperature) (+ (- (* 0.303439 (sqrt windSpeed)) (* 0.0202886 windSpeed)) 0.474266)))
)

(windchill 6 32.0)
26.8092
(defun fToC (temperature)
  (* (/ 5.0 9.0)(- temperature 32.0))
  )
(fToC 32.0)
0.0000
(defun cToF (temperature)
  (+ (* (/ 9.0 5.0) temperature) 32.0)
)
(cToF 0.0)
32.0000
(defun kToM (windSpeed)
  (* windSpeed 0.62)
)
(defun mToK (windSpeed)
  (/ windSpeed 0.62)
)
(mToK 6.0)
9.6774
(kToM 9.6774)
6.0000

(fToC (windchill (kToM 9.6774) (cToF 0.0)))
-2.8838
(fToC (windchill 6 32.0))
-2.8838
(fToC 26.8092)
-2.8838






