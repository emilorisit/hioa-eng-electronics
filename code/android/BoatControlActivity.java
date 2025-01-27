
package no.priv.enh.android.boatcontrol;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.util.Log;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.CompoundButton;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.android.future.usb.UsbAccessory;
import com.android.future.usb.UsbManager;

public class BoatControlActivity extends Activity {

    private static final String TAG = BoatControlActivity.class.getSimpleName(); // Debugging tag

    private PendingIntent mPermissionIntent;
    private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
    private boolean mPermissionRequestPending;

    private UsbManager mUsbManager;
    private UsbAccessory mAccessory;
    private ParcelFileDescriptor mFileDescriptor;
    private FileInputStream mInputStream;
    private FileOutputStream mOutputStream;

    // Global variables / commands
    private static final byte COMMAND_READING = 0x1;
    private static final byte COMMAND = 0x3;
    private static final byte TARGET_SPEED = 0x5;
    private static final byte TARGET_NM_PER_LITER = 0x6;
    private static final byte TARGET_FUEL_CONSUMPTION = 0x7;
    private static final byte TARGET_RELAY_PIN = 0x2;
    private static final byte TARGET_BATTERY_ONE_PIN = 0x8;
    private static final byte TARGET_BATTERY_TWO_PIN = 0x9;

    // Graphical elements
    private TextView speedTextView;
    private ProgressBar speedProgressBar;
    private TextView nmPerLiterTextView;
    private ProgressBar nmPerLiterProgressBar;
    private TextView fuelConsumptionTextView;
    private ProgressBar fuelConsumptionProgressBar;
    private TextView batteryOneTextView;
    private ProgressBar batteryOneProgressBar;
    private TextView batteryTwoTextView;
    private ProgressBar batteryTwoProgressBar;

    private ToggleButton relayToggleButton;
    private ToggleButton auxToggleButton;
    private ToggleButton radioToggleButton;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mUsbManager = UsbManager.getInstance(this);
        mPermissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(ACTION_USB_PERMISSION), 0);
        IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
        filter.addAction(UsbManager.ACTION_USB_ACCESSORY_DETACHED);
        registerReceiver(mUsbReceiver, filter);

        setContentView(R.layout.main);

        // Initialize graphical elements
        speedTextView = (TextView) findViewById(R.id.speed_text_view);
        speedProgressBar = (ProgressBar) findViewById(R.id.speed_bar);
        nmPerLiterTextView = (TextView) findViewById(R.id.nm_per_liter_text_view);
        nmPerLiterProgressBar = (ProgressBar) findViewById(R.id.nm_per_liter_bar);
        fuelConsumptionTextView = (TextView) findViewById(R.id.fuel_consumption_text_view);
        fuelConsumptionProgressBar = (ProgressBar) findViewById(R.id.fuel_consumption_bar);
        batteryOneTextView = (TextView) findViewById(R.id.battery_one_text_view);
        batteryOneProgressBar = (ProgressBar) findViewById(R.id.battery_one_bar);
        batteryTwoTextView = (TextView) findViewById(R.id.battery_two_text_view);
        batteryTwoProgressBar = (ProgressBar) findViewById(R.id.battery_two_bar);

        relayToggleButton = (ToggleButton) findViewById(R.id.relay_toggle_button);
        relayToggleButton.setOnCheckedChangeListener(toggleButtonCheckedListener);
        auxToggleButton = (ToggleButton) findViewById(R.id.aux_toggle_button);
        auxToggleButton.setOnCheckedChangeListener(toggleButtonCheckedListener);
        radioToggleButton = (ToggleButton) findViewById(R.id.radio_toggle_button);
        radioToggleButton.setOnCheckedChangeListener(toggleButtonCheckedListener);
    }

    @Override
    public void onResume() {
        super.onResume();
        // Code for USB accessory management
    }

    @Override
    public void onPause() {
        super.onPause();
        closeAccessory();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mUsbReceiver);
    }

    // Other methods omitted for brevity
}
