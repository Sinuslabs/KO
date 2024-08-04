namespace Router {
	
	const routes = Content.getAllComponents('_Route');
	const algo_routes = Content.getAllComponents('_AlgoRoute');
	
	for (route in routes) {
		route.setPaintRoutine(function(g) {});
	}
	
	for (route in algo_routes) {
		route.setPaintRoutine(function(g) {});
	}
	
	reg currentRoute = 'Main';
	
	inline function goToAlgoRoute(goToRoute) {
		
		if (!goToRoute) return;
		
		for (route in algo_routes) {
			if (route.getId().contains(goToRoute)) {
				currentRoute = goToRoute;
				route.set('visible', true);
			} else {
				route.set('visible', false);
			}
		}
		
	}
	
	inline function goTo(goToRoute) {
		
		if (!goToRoute) return;
		
		for (route in routes) {
			if (route.getId().contains(goToRoute)) {
				currentRoute = goToRoute;
				route.set('visible', true);
			} else {
				route.set('visible', false);
			}
		}
	}
}