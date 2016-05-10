# rails-windows-service
Run Ruby on Rails application as Windows service.
Rails web application is launched interactively as Windows batch file. It is stoped by pressing Ctrl-C. This service launches Rails application at "Service start" method and sends Ctrl-C to console of running Rails application at its "Stop service" method.
When developing, Rails was target but this service could be used for other command line applications which stops by invoking Ctrl-C.
