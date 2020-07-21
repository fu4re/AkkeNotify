#include "wintoastlib.h"

using namespace WinToastLib;

class WinToastHandlerExample : public IWinToastHandler {
public:
    void toastActivated() const override {
        std::wcout << L"The user clicked in this toast" << std::endl;
        exit(0);
    }

    void toastActivated(int actionIndex) const override {
        std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
        exit(16 + actionIndex);
    }

    void toastDismissed(WinToastDismissalReason state) const override {
        switch (state) {
        case UserCanceled:
            std::wcout << L"The user dismissed this toast" << std::endl;
            exit(1);
            break;
        case TimedOut:
            std::wcout << L"The toast has timed out" << std::endl;
            exit(2);
            break;
        case ApplicationHidden:
            std::wcout << L"The application hid the toast using ToastNotifier.hide()" << std::endl;
            exit(3);
            break;
        default:
            std::wcout << L"Toast not activated" << std::endl;
            exit(4);
            break;
        }
    }

    void toastFailed() const override {
        std::wcout << L"Error showing current toast" << std::endl;
        exit(5);
    }
};

int main()
{
	if (!WinToast::isCompatible())
	{
		std::wcout << L"Error, your system in not supported!" << std::endl;
		return -1;
	}

	WinToast::instance()->setAppName(L"AkkeNotify");
	const auto aumi = WinToast::configureAUMI(L"Akke", L"AkkeNotify", L"Photoshop", L"20161006");
	WinToast::instance()->setAppUserModelId(aumi);

	if (!WinToast::instance()->initialize()) {
		std::wcout << L"Error, could not initialize WinToast!" << std::endl;
        return -2;
	}

	WinToastHandlerExample* handler = new WinToastHandlerExample;
	WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText02);
	templ.setImagePath(L"image329.jpg");
	templ.setTextField(L"Hello", WinToastTemplate::FirstLine);
	templ.setTextField(L"World", WinToastTemplate::SecondLine);

    if (!WinToast::instance()->showToast(templ, handler)) {
        std::wcout << L"Error: Could not launch your toast notification!" << std::endl;
        return -3;
    }

    return 0;
}

