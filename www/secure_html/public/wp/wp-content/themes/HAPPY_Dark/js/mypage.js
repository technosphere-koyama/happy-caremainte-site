var ctx = document.getElementById("DoughnutChart");
var DoughnutChart = new Chart(ctx, {
	type: 'doughnut',
	data: {
		datasets: [{
			backgroundColor: [
				"#6a3b93",
				"#e0e0e0",
			],
			data: [25, 75],
			borderWidth: [0],
			borderColor: 'transparent'
		}]
	},
	options: {
		legend: {
			display: false
		},
		tooltips: { enabled: false },
		cutoutPercentage : 90

	}
});
