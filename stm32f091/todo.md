- handle errors from `AT+CIPSEND`, these look like this:
  ```
  > AT0,CONNECT

  > +IPD,0,15:last-records 5<0a>
  < AT+CIPSEND=0,125
  > AT+CIPSEND=0,125

  > ERROR
  ```
