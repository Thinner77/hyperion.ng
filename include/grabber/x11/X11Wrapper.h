#pragma once

#include <hyperion/GrabberWrapper.h>
#include <grabber/x11/X11Grabber.h>
// some include of xorg defines "None" this is also used by QT and has to be undefined to avoid collisions
#ifdef None
	#undef None
#endif

///
/// The X11Wrapper uses an instance of the X11Grabber to obtain ImageRgb's from the displayed content.
/// This ImageRgb is processed to a ColorRgb for each led and committed to the attached Hyperion.
///
class X11Wrapper: public GrabberWrapper
{
public:
	static constexpr const char* GRABBERTYPE = "X11";

	///
	/// Constructs the X11 frame grabber with a specified grab size and update rate.
	///
	/// @param[in] updateRate_Hz  The image grab rate [Hz]
	/// @param[in] pixelDecimation   Decimation factor for image [pixels]
	///
	X11Wrapper(	int updateRate_Hz=GrabberWrapper::DEFAULT_RATE_HZ,
				int pixelDecimation=GrabberWrapper::DEFAULT_PIXELDECIMATION,
				int cropLeft=0, int cropRight=0,
				int cropTop=0, int cropBottom=0
				);

	///
	/// Constructs the X11 frame grabber from configuration settings
	///
	X11Wrapper(const QJsonDocument& grabberConfig = QJsonDocument());

	///
	/// Destructor of this frame grabber. Releases any claimed resources.
	///
	~X11Wrapper() override;

	///
	/// @brief Determine if the grabber is available for usage on the platform
	///
	/// @return true, on success, else false
	///
	bool isAvailable() override;

	///
	/// Starts the grabber, if available
	///
	bool start() override;

	///
	/// Starts the grabber which produces led values with the specified update rate
	///
	bool open() override;

public slots:
	///
	/// Performs a single frame grab and computes the led-colors
	///
	void action() override;

private:
	/// The actual grabber
	X11Grabber _grabber;

	bool _init;
};
